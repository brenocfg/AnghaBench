#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_10__ {int sig; int hash; int sigandhash; } ;
struct TYPE_9__ {TYPE_2__* s3; } ;
struct TYPE_7__ {int* peer_sigalgs; size_t peer_sigalgslen; } ;
struct TYPE_8__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ SIGALG_LOOKUP ;

/* Variables and functions */
 size_t INT_MAX ; 
 int NID_undef ; 
 TYPE_4__* tls1_lookup_sigalg (int) ; 

int SSL_get_sigalgs(SSL *s, int idx,
                    int *psign, int *phash, int *psignhash,
                    unsigned char *rsig, unsigned char *rhash)
{
    uint16_t *psig = s->s3->tmp.peer_sigalgs;
    size_t numsigalgs = s->s3->tmp.peer_sigalgslen;
    if (psig == NULL || numsigalgs > INT_MAX)
        return 0;
    if (idx >= 0) {
        const SIGALG_LOOKUP *lu;

        if (idx >= (int)numsigalgs)
            return 0;
        psig += idx;
        if (rhash != NULL)
            *rhash = (unsigned char)((*psig >> 8) & 0xff);
        if (rsig != NULL)
            *rsig = (unsigned char)(*psig & 0xff);
        lu = tls1_lookup_sigalg(*psig);
        if (psign != NULL)
            *psign = lu != NULL ? lu->sig : NID_undef;
        if (phash != NULL)
            *phash = lu != NULL ? lu->hash : NID_undef;
        if (psignhash != NULL)
            *psignhash = lu != NULL ? lu->sigandhash : NID_undef;
    }
    return (int)numsigalgs;
}