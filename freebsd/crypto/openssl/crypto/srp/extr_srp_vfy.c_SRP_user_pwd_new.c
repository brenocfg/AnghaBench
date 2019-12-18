#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * info; int /*<<< orphan*/ * id; int /*<<< orphan*/ * v; int /*<<< orphan*/ * s; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; } ;
typedef  TYPE_1__ SRP_user_pwd ;

/* Variables and functions */
 TYPE_1__* OPENSSL_malloc (int) ; 

__attribute__((used)) static SRP_user_pwd *SRP_user_pwd_new(void)
{
    SRP_user_pwd *ret;

    if ((ret = OPENSSL_malloc(sizeof(*ret))) == NULL) {
        /* SRPerr(SRP_F_SRP_USER_PWD_NEW, ERR_R_MALLOC_FAILURE); */ /*ckerr_ignore*/
        return NULL;
    }
    ret->N = NULL;
    ret->g = NULL;
    ret->s = NULL;
    ret->v = NULL;
    ret->id = NULL;
    ret->info = NULL;
    return ret;
}