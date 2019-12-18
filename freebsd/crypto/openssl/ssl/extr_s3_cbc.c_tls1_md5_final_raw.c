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
struct TYPE_2__ {int /*<<< orphan*/  D; int /*<<< orphan*/  C; int /*<<< orphan*/  B; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  u32toLE (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void tls1_md5_final_raw(void *ctx, unsigned char *md_out)
{
    MD5_CTX *md5 = ctx;
    u32toLE(md5->A, md_out);
    u32toLE(md5->B, md_out);
    u32toLE(md5->C, md_out);
    u32toLE(md5->D, md_out);
}