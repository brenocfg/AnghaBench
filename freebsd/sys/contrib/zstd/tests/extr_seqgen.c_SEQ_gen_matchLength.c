#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int pos; scalar_t__ dst; } ;
struct TYPE_5__ {int state; int bytesLeft; int saved; int /*<<< orphan*/  xxh; int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ SEQ_stream ;
typedef  TYPE_2__ SEQ_outBuffer ;
typedef  int BYTE ;

/* Variables and functions */
 size_t MIN (int,size_t) ; 
 int SEQ_randByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,int* const,int) ; 
 int /*<<< orphan*/  memset (int*,int,size_t const) ; 

__attribute__((used)) static size_t SEQ_gen_matchLength(SEQ_stream* stream, unsigned value,
                                  SEQ_outBuffer* out)
{
    typedef enum {
        ml_first_byte = 0,
        ml_match_bytes,
        ml_last_byte,
    } ml_state;
    BYTE* const ostart = (BYTE*)out->dst;
    BYTE* const oend = ostart + out->size;
    BYTE* op = ostart + out->pos;

    switch ((ml_state)stream->state) {
    case ml_first_byte:
        /* Generate a single byte and pick a different byte for the match */
        if (op >= oend) {
            stream->bytesLeft = 1;
            break;
        }
        *op = SEQ_randByte(&stream->seed) & 0xFF;
        do {
            stream->saved = SEQ_randByte(&stream->seed) & 0xFF;
        } while (*op == stream->saved);
        ++op;
        /* State transition */
        stream->state = ml_match_bytes;
        stream->bytesLeft = value + 1;
    /* fall-through */
    case ml_match_bytes: {
        /* Copy matchLength + 1 bytes to the output buffer */
        size_t const setLength = MIN(stream->bytesLeft, (size_t)(oend - op));
        if (setLength > 0) {
            memset(op, stream->saved, setLength);
            op += setLength;
            stream->bytesLeft -= setLength;
        }
        if (stream->bytesLeft > 0)
            break;
        /* State transition */
        stream->state = ml_last_byte;
    }
    /* fall-through */
    case ml_last_byte:
        /* Generate a single byte and pick a different byte for the match */
        if (op >= oend) {
            stream->bytesLeft = 1;
            break;
        }
        do {
            *op = SEQ_randByte(&stream->seed) & 0xFF;
        } while (*op == stream->saved);
        ++op;
        /* State transition */
    /* fall-through */
    default:
        stream->state = 0;
        stream->bytesLeft = 0;
        break;
    }
    XXH64_update(&stream->xxh, ostart + out->pos, (op - ostart) - out->pos);
    out->pos = op - ostart;
    return stream->bytesLeft;
}