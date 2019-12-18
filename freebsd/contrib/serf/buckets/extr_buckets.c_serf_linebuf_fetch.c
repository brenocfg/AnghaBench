#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; size_t used; int /*<<< orphan*/ * line; } ;
typedef  TYPE_1__ serf_linebuf_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_EAGAIN ; 
 scalar_t__ APR_EGENERAL ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 scalar_t__ SERF_LINEBUF_CRLF_SPLIT ; 
 scalar_t__ SERF_LINEBUF_EMPTY ; 
 scalar_t__ SERF_LINEBUF_PARTIAL ; 
 scalar_t__ SERF_LINEBUF_READY ; 
 int SERF_NEWLINE_CRLF ; 
 int SERF_NEWLINE_CRLF_SPLIT ; 
 int SERF_NEWLINE_NONE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ serf_bucket_peek (int /*<<< orphan*/ *,char const**,int*) ; 
 int /*<<< orphan*/  serf_bucket_read (int /*<<< orphan*/ *,int,char const**,int*) ; 
 scalar_t__ serf_bucket_readline (int /*<<< orphan*/ *,int,int*,char const**,int*) ; 

apr_status_t serf_linebuf_fetch(
    serf_linebuf_t *linebuf,
    serf_bucket_t *bucket,
    int acceptable)
{
    /* If we had a complete line, then assume the caller has used it, so
     * we can now reset the state.
     */
    if (linebuf->state == SERF_LINEBUF_READY) {
        linebuf->state = SERF_LINEBUF_EMPTY;

        /* Reset the line_used, too, so we don't have to test the state
         * before using this value.
         */
        linebuf->used = 0;
    }

    while (1) {
        apr_status_t status;
        const char *data;
        apr_size_t len;

        if (linebuf->state == SERF_LINEBUF_CRLF_SPLIT) {
            /* On the previous read, we received just a CR. The LF might
             * be present, but the bucket couldn't see it. We need to
             * examine a single character to determine how to handle the
             * split CRLF.
             */

            status = serf_bucket_peek(bucket, &data, &len);
            if (SERF_BUCKET_READ_ERROR(status))
                return status;

            if (len > 0) {
                if (*data == '\n') {
                    /* We saw the second part of CRLF. We don't need to
                     * save that character, so do an actual read to suck
                     * up that character.
                     */
                    /* ### check status */
                    (void) serf_bucket_read(bucket, 1, &data, &len);
                }
                /* else:
                 *   We saw the first character of the next line. Thus,
                 *   the current line is terminated by the CR. Just
                 *   ignore whatever we peeked at. The next reader will
                 *   see it and handle it as appropriate.
                 */

                /* Whatever was read, the line is now ready for use. */
                linebuf->state = SERF_LINEBUF_READY;
            } else {
                /* no data available, try again later. */
                return APR_EAGAIN;
            }
        }
        else {
            int found;

            status = serf_bucket_readline(bucket, acceptable, &found,
                                          &data, &len);
            if (SERF_BUCKET_READ_ERROR(status)) {
                return status;
            }
            /* Some bucket types (socket) might need an extra read to find
               out EOF state, so they'll return no data in that read. This
               means we're done reading, return what we got. */
            if (APR_STATUS_IS_EOF(status) && len == 0) {
	        return status;
            }
            if (linebuf->used + len > sizeof(linebuf->line)) {
                /* ### need a "line too long" error */
                return APR_EGENERAL;
            }

            /* Note: our logic doesn't change for SERF_LINEBUF_PARTIAL. That
             * only affects how we fill the buffer. It is a communication to
             * our caller on whether the line is ready or not.
             */

            /* If we didn't see a newline, then we should mark the line
             * buffer as partially complete.
             */
            if (found == SERF_NEWLINE_NONE) {
                linebuf->state = SERF_LINEBUF_PARTIAL;
            }
            else if (found == SERF_NEWLINE_CRLF_SPLIT) {
                linebuf->state = SERF_LINEBUF_CRLF_SPLIT;

                /* Toss the partial CR. We won't ever need it. */
                --len;
            }
            else {
                /* We got a newline (of some form). We don't need it
                 * in the line buffer, so back up the length. Then
                 * mark the line as ready.
                 */
                len -= 1 + (found == SERF_NEWLINE_CRLF);

                linebuf->state = SERF_LINEBUF_READY;
            }

            /* ### it would be nice to avoid this copy if at all possible,
               ### and just return the a data/len pair to the caller. we're
               ### keeping it simple for now. */
            memcpy(&linebuf->line[linebuf->used], data, len);
            linebuf->used += len;
        }

        /* If we saw anything besides "success. please read again", then
         * we should return that status. If the line was completed, then
         * we should also return.
         */
        if (status || linebuf->state == SERF_LINEBUF_READY)
            return status;

        /* We got APR_SUCCESS and the line buffer is not complete. Let's
         * loop to read some more data.
         */
    }
    /* NOTREACHED */
}