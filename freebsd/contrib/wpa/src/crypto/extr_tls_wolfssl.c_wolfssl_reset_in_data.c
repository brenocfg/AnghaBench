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
struct wpabuf {int dummy; } ;
struct tls_in_data {scalar_t__ consumed; struct wpabuf const* in_data; } ;

/* Variables and functions */

__attribute__((used)) static void wolfssl_reset_in_data(struct tls_in_data *in,
				  const struct wpabuf *buf)
{
	/* old one not owned by us so don't free */
	in->in_data = buf;
	in->consumed = 0;
}