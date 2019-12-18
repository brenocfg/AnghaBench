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
 size_t D_RC4 ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,size_t,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/ ** c ; 
 scalar_t__* lengths ; 
 int /*<<< orphan*/  rc4_ks ; 
 size_t testnum ; 

__attribute__((used)) static int RC4_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    unsigned char *buf = tempargs->buf;
    int count;
    for (count = 0; COND(c[D_RC4][testnum]); count++)
        RC4(&rc4_ks, (size_t)lengths[testnum], buf, buf);
    return count;
}