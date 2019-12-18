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
struct tls_out_data {int /*<<< orphan*/  out_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_alloc_copy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wolfssl_reset_out_data(struct tls_out_data *out)
{
	/* old one not owned by us so don't free */
	out->out_data = wpabuf_alloc_copy("", 0);
}