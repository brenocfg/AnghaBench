#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hx509_generate_private_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct hx509_generate_private_context*) ; 

void
_hx509_generate_private_key_free(struct hx509_generate_private_context **ctx)
{
    free(*ctx);
    *ctx = NULL;
}