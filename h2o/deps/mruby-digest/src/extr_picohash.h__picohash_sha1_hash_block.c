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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* state; int* buffer; } ;
typedef  TYPE_1__ _picohash_sha1_ctx_t ;

/* Variables and functions */
 int _PICOHASH_SHA1_K0 ; 
 int _PICOHASH_SHA1_K20 ; 
 int _PICOHASH_SHA1_K40 ; 
 int _PICOHASH_SHA1_K60 ; 
 int _picohash_sha1_rol32 (int,int) ; 

__attribute__((used)) static inline void _picohash_sha1_hash_block(_picohash_sha1_ctx_t *s)
{
    uint8_t i;
    uint32_t a, b, c, d, e, t;

    a = s->state[0];
    b = s->state[1];
    c = s->state[2];
    d = s->state[3];
    e = s->state[4];
    for (i = 0; i < 80; i++) {
        if (i >= 16) {
            t = s->buffer[(i + 13) & 15] ^ s->buffer[(i + 8) & 15] ^ s->buffer[(i + 2) & 15] ^ s->buffer[i & 15];
            s->buffer[i & 15] = _picohash_sha1_rol32(t, 1);
        }
        if (i < 20) {
            t = (d ^ (b & (c ^ d))) + _PICOHASH_SHA1_K0;
        } else if (i < 40) {
            t = (b ^ c ^ d) + _PICOHASH_SHA1_K20;
        } else if (i < 60) {
            t = ((b & c) | (d & (b | c))) + _PICOHASH_SHA1_K40;
        } else {
            t = (b ^ c ^ d) + _PICOHASH_SHA1_K60;
        }
        t += _picohash_sha1_rol32(a, 5) + e + s->buffer[i & 15];
        e = d;
        d = c;
        c = _picohash_sha1_rol32(b, 30);
        b = a;
        a = t;
    }
    s->state[0] += a;
    s->state[1] += b;
    s->state[2] += c;
    s->state[3] += d;
    s->state[4] += e;
}