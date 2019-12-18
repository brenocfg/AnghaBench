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
struct tls_context {int /*<<< orphan*/  cert_in_cb; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  event_cb; } ;
struct tls_config {int /*<<< orphan*/  cert_in_cb; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  event_cb; } ;

/* Variables and functions */
 struct tls_context* os_zalloc (int) ; 

__attribute__((used)) static struct tls_context * tls_context_new(const struct tls_config *conf)
{
	struct tls_context *context = os_zalloc(sizeof(*context));
	if (context == NULL)
		return NULL;
	if (conf) {
		context->event_cb = conf->event_cb;
		context->cb_ctx = conf->cb_ctx;
		context->cert_in_cb = conf->cert_in_cb;
	}
	return context;
}