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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct tws_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ tws_get_response (struct tws_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tws_drain_response_queue(struct tws_softc *sc)
{
    u_int16_t req_id;
    u_int64_t mfa;
    while ( tws_get_response(sc, &req_id, &mfa) );
}