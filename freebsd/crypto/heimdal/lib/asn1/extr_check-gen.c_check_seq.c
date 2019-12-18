#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ TESTSeqOf ;
typedef  int /*<<< orphan*/  TESTInteger ;

/* Variables and functions */
 int add_TESTSeqOf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_TESTSeqOf (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int remove_TESTSeqOf (TYPE_1__*,int) ; 

__attribute__((used)) static int
check_seq(void)
{
    TESTSeqOf seq;
    TESTInteger i;
    int ret;

    seq.val = NULL;
    seq.len = 0;

    ret = add_TESTSeqOf(&seq, &i);
    if (ret) { printf("failed adding\n"); goto out; }
    ret = add_TESTSeqOf(&seq, &i);
    if (ret) { printf("failed adding\n"); goto out; }
    ret = add_TESTSeqOf(&seq, &i);
    if (ret) { printf("failed adding\n"); goto out; }
    ret = add_TESTSeqOf(&seq, &i);
    if (ret) { printf("failed adding\n"); goto out; }

    ret = remove_TESTSeqOf(&seq, seq.len - 1);
    if (ret) { printf("failed removing\n"); goto out; }
    ret = remove_TESTSeqOf(&seq, 2);
    if (ret) { printf("failed removing\n"); goto out; }
    ret = remove_TESTSeqOf(&seq, 0);
    if (ret) { printf("failed removing\n"); goto out; }
    ret = remove_TESTSeqOf(&seq, 0);
    if (ret) { printf("failed removing\n"); goto out; }
    ret = remove_TESTSeqOf(&seq, 0);
    if (ret == 0) {
	printf("can remove from empty list");
	return 1;
    }

    if (seq.len != 0) {
	printf("seq not empty!");
	return 1;
    }
    free_TESTSeqOf(&seq);
    ret = 0;

out:

    return ret;
}