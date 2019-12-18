#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  allocator; TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_14__ {unsigned long total_out; unsigned char* next_in; int /*<<< orphan*/ * avail_in; int /*<<< orphan*/ * avail_out; scalar_t__ next_out; } ;
struct TYPE_16__ {int state; unsigned long crc; void* stream_status; TYPE_1__* stream; TYPE_1__* inflate_stream; int /*<<< orphan*/ * stream_size; int /*<<< orphan*/ * stream_left; int /*<<< orphan*/  format; TYPE_10__ zstream; int /*<<< orphan*/ * bufferSize; scalar_t__ buffer; int /*<<< orphan*/  windowSize; int /*<<< orphan*/ * hdr_buffer; } ;
typedef  TYPE_2__ deflate_context_t ;
typedef  void* apr_status_t ;
typedef  int /*<<< orphan*/ * apr_size_t ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 void* APR_EGENERAL ; 
 int /*<<< orphan*/  APR_STATUS_IS_EAGAIN (void*) ; 
 int /*<<< orphan*/  APR_STATUS_IS_EOF (void*) ; 
 void* APR_SUCCESS ; 
 int /*<<< orphan*/ * DEFLATE_VERIFY_SIZE ; 
 int /*<<< orphan*/  SERF_BUCKET_READ_ERROR (void*) ; 
 TYPE_1__* SERF_BUCKET_SIMPLE_STRING_LEN (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SERF_DEFLATE_DEFLATE 137 
#define  SERF_DEFLATE_GZIP 136 
 void* SERF_ERROR_DECOMPRESSION_FAILED ; 
#define  STATE_DONE 135 
#define  STATE_FINISH 134 
#define  STATE_HEADER 133 
#define  STATE_INFLATE 132 
#define  STATE_INIT 131 
#define  STATE_READING_HEADER 130 
#define  STATE_READING_VERIFY 129 
#define  STATE_VERIFY 128 
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 void* crc32 (unsigned long,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * deflate_magic ; 
 unsigned long getLong (unsigned char*) ; 
 int inflate (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_10__*) ; 
 int inflateInit2 (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_append (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_aggregate_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_prepend (TYPE_1__*,TYPE_1__*) ; 
 void* serf_bucket_read (TYPE_1__*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ **) ; 

__attribute__((used)) static apr_status_t serf_deflate_read(serf_bucket_t *bucket,
                                      apr_size_t requested,
                                      const char **data, apr_size_t *len)
{
    deflate_context_t *ctx = bucket->data;
    apr_status_t status;
    const char *private_data;
    apr_size_t private_len;
    int zRC;

    while (1) {
        switch (ctx->state) {
        case STATE_READING_HEADER:
        case STATE_READING_VERIFY:
            status = serf_bucket_read(ctx->stream, ctx->stream_left,
                                      &private_data, &private_len);

            if (SERF_BUCKET_READ_ERROR(status)) {
                return status;
            }

            memcpy(ctx->hdr_buffer + (ctx->stream_size - ctx->stream_left),
                   private_data, private_len);

            ctx->stream_left -= private_len;

            if (ctx->stream_left == 0) {
                ctx->state++;
                if (APR_STATUS_IS_EAGAIN(status)) {
                    *len = 0;
                    return status;
                }
            }
            else if (status) {
                *len = 0;
                return status;
            }
            break;
        case STATE_HEADER:
            if (ctx->hdr_buffer[0] != deflate_magic[0] ||
                ctx->hdr_buffer[1] != deflate_magic[1]) {
                return SERF_ERROR_DECOMPRESSION_FAILED;
            }
            if (ctx->hdr_buffer[3] != 0) {
                return SERF_ERROR_DECOMPRESSION_FAILED;
            }
            ctx->state++;
            break;
        case STATE_VERIFY:
        {
            unsigned long compCRC, compLen, actualLen;

            /* Do the checksum computation. */
            compCRC = getLong((unsigned char*)ctx->hdr_buffer);
            if (ctx->crc != compCRC) {
                return SERF_ERROR_DECOMPRESSION_FAILED;
            }
            compLen = getLong((unsigned char*)ctx->hdr_buffer + 4);
            /* The length in the trailer is module 2^32, so do the same for
               the actual length. */
            actualLen = ctx->zstream.total_out;
            actualLen &= 0xFFFFFFFF;
            if (actualLen != compLen) {
                return SERF_ERROR_DECOMPRESSION_FAILED;
            }
            ctx->state++;
            break;
        }
        case STATE_INIT:
            zRC = inflateInit2(&ctx->zstream, ctx->windowSize);
            if (zRC != Z_OK) {
                return SERF_ERROR_DECOMPRESSION_FAILED;
            }
            ctx->zstream.next_out = ctx->buffer;
            ctx->zstream.avail_out = ctx->bufferSize;
            ctx->state++;
            break;
        case STATE_FINISH:
            inflateEnd(&ctx->zstream);
            serf_bucket_aggregate_prepend(ctx->stream, ctx->inflate_stream);
            ctx->inflate_stream = 0;
            ctx->state++;
            break;
        case STATE_INFLATE:
            /* Do we have anything already uncompressed to read? */
            status = serf_bucket_read(ctx->inflate_stream, requested, data,
                                      len);
            if (SERF_BUCKET_READ_ERROR(status)) {
                return status;
            }
            /* Hide EOF. */
            if (APR_STATUS_IS_EOF(status)) {
                status = ctx->stream_status;
                if (APR_STATUS_IS_EOF(status)) {
                    /* We've read all of the data from our stream, but we
                     * need to continue to iterate until we flush
                     * out the zlib buffer.
                     */
                    status = APR_SUCCESS;
                }
            }
            if (*len != 0) {
                return status;
            }

            /* We tried; but we have nothing buffered. Fetch more. */

            /* It is possible that we maxed out avail_out before
             * exhausting avail_in; therefore, continue using the
             * previous buffer.  Otherwise, fetch more data from
             * our stream bucket.
             */
            if (ctx->zstream.avail_in == 0) {
                /* When we empty our inflated stream, we'll return this
                 * status - this allow us to eventually pass up EAGAINs.
                 */
                ctx->stream_status = serf_bucket_read(ctx->stream,
                                                      ctx->bufferSize,
                                                      &private_data,
                                                      &private_len);

                if (SERF_BUCKET_READ_ERROR(ctx->stream_status)) {
                    return ctx->stream_status;
                }

                if (!private_len && APR_STATUS_IS_EAGAIN(ctx->stream_status)) {
                    *len = 0;
                    status = ctx->stream_status;
                    ctx->stream_status = APR_SUCCESS;
                    return status;
                }

                ctx->zstream.next_in = (unsigned char*)private_data;
                ctx->zstream.avail_in = private_len;
            }

            while (1) {

                zRC = inflate(&ctx->zstream, Z_NO_FLUSH);

                /* We're full or zlib requires more space. Either case, clear
                   out our buffer, reset, and return. */
                if (zRC == Z_BUF_ERROR || ctx->zstream.avail_out == 0) {
                    serf_bucket_t *tmp;
                    ctx->zstream.next_out = ctx->buffer;
                    private_len = ctx->bufferSize - ctx->zstream.avail_out;

                    ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer,
                                     private_len);

                    /* FIXME: There probably needs to be a free func. */
                    tmp = SERF_BUCKET_SIMPLE_STRING_LEN((char *)ctx->buffer,
                                                        private_len,
                                                        bucket->allocator);
                    serf_bucket_aggregate_append(ctx->inflate_stream, tmp);
                    ctx->zstream.avail_out = ctx->bufferSize;
                    break;
                }

                if (zRC == Z_STREAM_END) {
                    serf_bucket_t *tmp;

                    private_len = ctx->bufferSize - ctx->zstream.avail_out;
                    ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer,
                                     private_len);
                    /* FIXME: There probably needs to be a free func. */
                    tmp = SERF_BUCKET_SIMPLE_STRING_LEN((char *)ctx->buffer,
                                                        private_len,
                                                        bucket->allocator);
                    serf_bucket_aggregate_append(ctx->inflate_stream, tmp);

                    ctx->zstream.avail_out = ctx->bufferSize;

                    /* Push back the remaining data to be read. */
                    tmp = serf_bucket_aggregate_create(bucket->allocator);
                    serf_bucket_aggregate_prepend(tmp, ctx->stream);
                    ctx->stream = tmp;

                    /* We now need to take the remaining avail_in and
                     * throw it in ctx->stream so our next read picks it up.
                     */
                    tmp = SERF_BUCKET_SIMPLE_STRING_LEN(
                                        (const char*)ctx->zstream.next_in,
                                                     ctx->zstream.avail_in,
                                                     bucket->allocator);
                    serf_bucket_aggregate_prepend(ctx->stream, tmp);

                    switch (ctx->format) {
                    case SERF_DEFLATE_GZIP:
                        ctx->stream_left = ctx->stream_size =
                            DEFLATE_VERIFY_SIZE;
                        ctx->state++;
                        break;
                    case SERF_DEFLATE_DEFLATE:
                        /* Deflate does not have a verify footer. */
                        ctx->state = STATE_FINISH;
                        break;
                    default:
                        /* Not reachable */
                        return APR_EGENERAL;
                    }

                    break;
                }

                /* Any other error? */
                if (zRC != Z_OK) {
                    return SERF_ERROR_DECOMPRESSION_FAILED;
                }

                /* As long as zRC == Z_OK, just keep looping. */
            }
            /* Okay, we've inflated.  Try to read. */
            status = serf_bucket_read(ctx->inflate_stream, requested, data,
                                      len);
            /* Hide EOF. */
            if (APR_STATUS_IS_EOF(status)) {
                status = ctx->stream_status;

                /* If the inflation wasn't finished, return APR_SUCCESS. */
                if (zRC != Z_STREAM_END)
                    return APR_SUCCESS;

                /* If our stream is finished too and all data was inflated,
                 * return SUCCESS so we'll iterate one more time.
                 */
                if (APR_STATUS_IS_EOF(status)) {
                    /* No more data to read from the stream, and everything
                       inflated. If all data was received correctly, state
                       should have been advanced to STATE_READING_VERIFY or
                       STATE_FINISH. If not, then the data was incomplete
                       and we have an error. */
                    if (ctx->state != STATE_INFLATE)
                        return APR_SUCCESS;
                    else
                        return SERF_ERROR_DECOMPRESSION_FAILED;
                }
            }
            return status;
        case STATE_DONE:
            /* We're done inflating.  Use our finished buffer. */
            return serf_bucket_read(ctx->stream, requested, data, len);
        default:
            /* Not reachable */
            return APR_EGENERAL;
        }
    }

    /* NOTREACHED */
}