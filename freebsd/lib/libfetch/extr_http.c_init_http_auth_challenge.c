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
struct TYPE_3__ {scalar_t__ nc; scalar_t__ stale; int /*<<< orphan*/ * algo; int /*<<< orphan*/  opaque; int /*<<< orphan*/  nonce; int /*<<< orphan*/  qop; int /*<<< orphan*/  realm; int /*<<< orphan*/  scheme; } ;
typedef  TYPE_1__ http_auth_challenge_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPAS_UNKNOWN ; 

__attribute__((used)) static void
init_http_auth_challenge(http_auth_challenge_t *b)
{
	b->scheme = HTTPAS_UNKNOWN;
	b->realm = b->qop = b->nonce = b->opaque = b->algo = NULL;
	b->stale = b->nc = 0;
}