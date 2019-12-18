#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pr_policy; } ;
struct TYPE_7__ {TYPE_1__ prinfo; } ;
typedef  TYPE_2__ bio_dgram_sctp_data ;
struct TYPE_8__ {scalar_t__ flags; TYPE_2__* ptr; scalar_t__ num; scalar_t__ init; } ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_DGRAM_SCTP_NEW ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SCTP_PR_SCTP_NONE ; 

__attribute__((used)) static int dgram_sctp_new(BIO *bi)
{
    bio_dgram_sctp_data *data = NULL;

    bi->init = 0;
    bi->num = 0;
    if ((data = OPENSSL_zalloc(sizeof(*data))) == NULL) {
        BIOerr(BIO_F_DGRAM_SCTP_NEW, ERR_R_MALLOC_FAILURE);
        return 0;
    }
#  ifdef SCTP_PR_SCTP_NONE
    data->prinfo.pr_policy = SCTP_PR_SCTP_NONE;
#  endif
    bi->ptr = data;

    bi->flags = 0;
    return 1;
}