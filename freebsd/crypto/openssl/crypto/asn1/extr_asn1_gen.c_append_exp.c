#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int exp_tag; int exp_class; int exp_constructed; int exp_pad; } ;
typedef  TYPE_1__ tag_exp_type ;
struct TYPE_5__ {int imp_tag; scalar_t__ exp_count; int imp_class; TYPE_1__* exp_list; } ;
typedef  TYPE_2__ tag_exp_arg ;

/* Variables and functions */
 scalar_t__ ASN1_FLAG_EXP_MAX ; 
 int /*<<< orphan*/  ASN1_F_APPEND_EXP ; 
 int /*<<< orphan*/  ASN1_R_DEPTH_EXCEEDED ; 
 int /*<<< orphan*/  ASN1_R_ILLEGAL_IMPLICIT_TAG ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int append_exp(tag_exp_arg *arg, int exp_tag, int exp_class,
                      int exp_constructed, int exp_pad, int imp_ok)
{
    tag_exp_type *exp_tmp;
    /* Can only have IMPLICIT if permitted */
    if ((arg->imp_tag != -1) && !imp_ok) {
        ASN1err(ASN1_F_APPEND_EXP, ASN1_R_ILLEGAL_IMPLICIT_TAG);
        return 0;
    }

    if (arg->exp_count == ASN1_FLAG_EXP_MAX) {
        ASN1err(ASN1_F_APPEND_EXP, ASN1_R_DEPTH_EXCEEDED);
        return 0;
    }

    exp_tmp = &arg->exp_list[arg->exp_count++];

    /*
     * If IMPLICIT set tag to implicit value then reset implicit tag since it
     * has been used.
     */
    if (arg->imp_tag != -1) {
        exp_tmp->exp_tag = arg->imp_tag;
        exp_tmp->exp_class = arg->imp_class;
        arg->imp_tag = -1;
        arg->imp_class = -1;
    } else {
        exp_tmp->exp_tag = exp_tag;
        exp_tmp->exp_class = exp_class;
    }
    exp_tmp->exp_constructed = exp_constructed;
    exp_tmp->exp_pad = exp_pad;

    return 1;
}