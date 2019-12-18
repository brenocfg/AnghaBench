#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ password; scalar_t__ user; scalar_t__ realm; scalar_t__ scheme; } ;
typedef  TYPE_1__ http_auth_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  init_http_auth_params (TYPE_1__*) ; 

__attribute__((used)) static void
clean_http_auth_params(http_auth_params_t *s)
{
	if (s->scheme)
		free(s->scheme);
	if (s->realm)
		free(s->realm);
	if (s->user)
		free(s->user);
	if (s->password)
		free(s->password);
	init_http_auth_params(s);
}