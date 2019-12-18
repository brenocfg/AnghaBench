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
struct TYPE_3__ {int num; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ptr; scalar_t__ init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLAGS_UPLINK ; 

__attribute__((used)) static int fd_new(BIO *bi)
{
    bi->init = 0;
    bi->num = -1;
    bi->ptr = NULL;
    bi->flags = BIO_FLAGS_UPLINK; /* essentially redundant */
    return 1;
}