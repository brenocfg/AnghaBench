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
struct httpread {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* cb ) (struct httpread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPREAD_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  stub1 (struct httpread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct httpread*) ; 

__attribute__((used)) static void httpread_timeout_handler(void *eloop_data, void *user_ctx)
{
	struct httpread *h = user_ctx;
	wpa_printf(MSG_DEBUG, "httpread timeout (%p)", h);
	(*h->cb)(h, h->cookie, HTTPREAD_EVENT_TIMEOUT);
}