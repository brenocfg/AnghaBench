#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* buf; } ;
typedef  TYPE_1__ loopargs_t ;

/* Variables and functions */
 scalar_t__ COND (int /*<<< orphan*/ ) ; 
 size_t D_MD5 ; 
 int /*<<< orphan*/  MD5 (unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/ ** c ; 
 int /*<<< orphan*/ * lengths ; 
 size_t testnum ; 

__attribute__((used)) static int MD5_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    unsigned char md5[MD5_DIGEST_LENGTH];
    int count;
    for (count = 0; COND(c[D_MD5][testnum]); count++)
        MD5(buf, lengths[testnum], md5);
    return count;
}