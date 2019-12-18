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
struct TYPE_4__ {int /*<<< orphan*/  client_random; } ;
typedef  TYPE_1__ ptls_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_RANDOM ; 
 int /*<<< orphan*/  PTLS_PROBE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloca (int) ; 
 int /*<<< orphan*/  ptls_hexdump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void log_client_random(ptls_t *tls)
{
    PTLS_PROBE(CLIENT_RANDOM, tls,
               ptls_hexdump(alloca(sizeof(tls->client_random) * 2 + 1), tls->client_random, sizeof(tls->client_random)));
}