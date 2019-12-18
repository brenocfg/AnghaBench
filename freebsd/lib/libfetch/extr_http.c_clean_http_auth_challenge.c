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
struct TYPE_4__ {scalar_t__ algo; scalar_t__ opaque; scalar_t__ nonce; scalar_t__ qop; scalar_t__ realm; } ;
typedef  TYPE_1__ http_auth_challenge_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  init_http_auth_challenge (TYPE_1__*) ; 

__attribute__((used)) static void
clean_http_auth_challenge(http_auth_challenge_t *b)
{
	if (b->realm)
		free(b->realm);
	if (b->qop)
		free(b->qop);
	if (b->nonce)
		free(b->nonce);
	if (b->opaque)
		free(b->opaque);
	if (b->algo)
		free(b->algo);
	init_http_auth_challenge(b);
}