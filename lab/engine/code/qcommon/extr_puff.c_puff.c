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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct state {void* incnt; void* outcnt; int /*<<< orphan*/  env; scalar_t__ bitcnt; scalar_t__ bitbuf; void* inlen; int /*<<< orphan*/ * in; void* outlen; int /*<<< orphan*/ * out; } ;
typedef  int int32_t ;

/* Variables and functions */
 int bits (struct state*,int) ; 
 int dynamic (struct state*) ; 
 int fixed (struct state*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int stored (struct state*) ; 

int32_t puff(uint8_t  *dest,           /* pointer to destination pointer */
             uint32_t *destlen,        /* amount of output space */
             uint8_t  *source,         /* pointer to source data pointer */
             uint32_t *sourcelen)      /* amount of input available */
{
    struct state s;             /* input/output state */
    int32_t last, type;             /* block information */
    int32_t err;                    /* return value */

    /* initialize output state */
    s.out = dest;
    s.outlen = *destlen;                /* ignored if dest is NULL */
    s.outcnt = 0;

    /* initialize input state */
    s.in = source;
    s.inlen = *sourcelen;
    s.incnt = 0;
    s.bitbuf = 0;
    s.bitcnt = 0;

    /* return if bits() or decode() tries to read past available input */
    if (setjmp(s.env) != 0)             /* if came back here via longjmp() */
        err = 2;                        /* then skip do-loop, return error */
    else {
        /* process blocks until last block or error */
        do {
            last = bits(&s, 1);         /* one if last block */
            type = bits(&s, 2);         /* block type 0..3 */
            err = type == 0 ? stored(&s) :
                  (type == 1 ? fixed(&s) :
                   (type == 2 ? dynamic(&s) :
                    -1));               /* type == 3, invalid */
            if (err != 0) break;        /* return with error */
        } while (!last);
    }

    /* update the lengths and return */
    if (err <= 0) {
        *destlen = s.outcnt;
        *sourcelen = s.incnt;
    }
    return err;
}