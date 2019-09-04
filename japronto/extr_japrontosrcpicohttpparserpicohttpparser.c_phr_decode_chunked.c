#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct phr_chunked_decoder {int _state; int _hex_count; int bytes_left_in_chunk; int /*<<< orphan*/  consume_trailer; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  CHUNKED_IN_CHUNK_CRLF 133 
#define  CHUNKED_IN_CHUNK_DATA 132 
#define  CHUNKED_IN_CHUNK_EXT 131 
#define  CHUNKED_IN_CHUNK_SIZE 130 
#define  CHUNKED_IN_TRAILERS_LINE_HEAD 129 
#define  CHUNKED_IN_TRAILERS_LINE_MIDDLE 128 
 int /*<<< orphan*/  assert (int) ; 
 int decode_hex (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

ssize_t phr_decode_chunked(struct phr_chunked_decoder *decoder, char *buf, size_t *_bufsz)
{
    size_t dst = 0, src = 0, bufsz = *_bufsz;
    ssize_t ret = -2; /* incomplete */

    while (1) {
        switch (decoder->_state) {
        case CHUNKED_IN_CHUNK_SIZE:
            for (;; ++src) {
                int v;
                if (src == bufsz)
                    goto Exit;
                if ((v = decode_hex(buf[src])) == -1) {
                    if (decoder->_hex_count == 0) {
                        ret = -1;
                        goto Exit;
                    }
                    break;
                }
                if (decoder->_hex_count == sizeof(size_t) * 2) {
                    ret = -1;
                    goto Exit;
                }
                decoder->bytes_left_in_chunk = decoder->bytes_left_in_chunk * 16 + v;
                ++decoder->_hex_count;
            }
            decoder->_hex_count = 0;
            decoder->_state = CHUNKED_IN_CHUNK_EXT;
        /* fallthru */
        case CHUNKED_IN_CHUNK_EXT:
            /* RFC 7230 A.2 "Line folding in chunk extensions is disallowed" */
            for (;; ++src) {
                if (src == bufsz)
                    goto Exit;
                if (buf[src] == '\012')
                    break;
            }
            ++src;
            if (decoder->bytes_left_in_chunk == 0) {
                if (decoder->consume_trailer) {
                    decoder->_state = CHUNKED_IN_TRAILERS_LINE_HEAD;
                    break;
                } else {
                    goto Complete;
                }
            }
            decoder->_state = CHUNKED_IN_CHUNK_DATA;
        /* fallthru */
        case CHUNKED_IN_CHUNK_DATA: {
            size_t avail = bufsz - src;
            if (avail < decoder->bytes_left_in_chunk) {
                if (dst != src)
                    memmove(buf + dst, buf + src, avail);
                src += avail;
                dst += avail;
                decoder->bytes_left_in_chunk -= avail;
                goto Exit;
            }
            if (dst != src)
                memmove(buf + dst, buf + src, decoder->bytes_left_in_chunk);
            src += decoder->bytes_left_in_chunk;
            dst += decoder->bytes_left_in_chunk;
            decoder->bytes_left_in_chunk = 0;
            decoder->_state = CHUNKED_IN_CHUNK_CRLF;
        }
        /* fallthru */
        case CHUNKED_IN_CHUNK_CRLF:
            for (;; ++src) {
                if (src == bufsz)
                    goto Exit;
                if (buf[src] != '\015')
                    break;
            }
            if (buf[src] != '\012') {
                ret = -1;
                goto Exit;
            }
            ++src;
            decoder->_state = CHUNKED_IN_CHUNK_SIZE;
            break;
        case CHUNKED_IN_TRAILERS_LINE_HEAD:
            for (;; ++src) {
                if (src == bufsz)
                    goto Exit;
                if (buf[src] != '\015')
                    break;
            }
            if (buf[src++] == '\012')
                goto Complete;
            decoder->_state = CHUNKED_IN_TRAILERS_LINE_MIDDLE;
        /* fallthru */
        case CHUNKED_IN_TRAILERS_LINE_MIDDLE:
            for (;; ++src) {
                if (src == bufsz)
                    goto Exit;
                if (buf[src] == '\012')
                    break;
            }
            ++src;
            decoder->_state = CHUNKED_IN_TRAILERS_LINE_HEAD;
            break;
        default:
            assert(!"decoder is corrupt");
        }
    }

Complete:
    ret = bufsz - src;
Exit:
    if (dst != src)
        memmove(buf + dst, buf + src, bufsz - src);
    *_bufsz = dst;
    return ret;
}