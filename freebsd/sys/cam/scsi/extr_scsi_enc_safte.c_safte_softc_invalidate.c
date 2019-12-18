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
struct scfg {int /*<<< orphan*/  requests; } ;
struct TYPE_3__ {struct scfg* enc_private; } ;
typedef  TYPE_1__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  safte_terminate_control_requests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
safte_softc_invalidate(enc_softc_t *enc)
{
	struct scfg *cfg;

	cfg = enc->enc_private;
	safte_terminate_control_requests(&cfg->requests, ENXIO);
}