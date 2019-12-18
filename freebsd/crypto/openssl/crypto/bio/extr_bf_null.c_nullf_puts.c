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
struct TYPE_3__ {int /*<<< orphan*/ * next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int BIO_puts (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int nullf_puts(BIO *bp, const char *str)
{
    if (bp->next_bio == NULL)
        return 0;
    return BIO_puts(bp->next_bio, str);
}