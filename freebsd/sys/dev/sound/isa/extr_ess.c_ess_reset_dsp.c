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
struct ess_info {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SBDSP_RST ; 
 int /*<<< orphan*/  ess_cmd (struct ess_info*,int) ; 
 int ess_get_byte (struct ess_info*) ; 
 int /*<<< orphan*/  ess_wr (struct ess_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ess_reset_dsp(struct ess_info *sc)
{
    	ess_wr(sc, SBDSP_RST, 3);
    	DELAY(100);
    	ess_wr(sc, SBDSP_RST, 0);
    	if (ess_get_byte(sc) != 0xAA) {
        	DEB(printf("ess_reset_dsp 0x%lx failed\n",
			   rman_get_start(sc->io_base)));
		return ENXIO;	/* Sorry */
    	}
    	ess_cmd(sc, 0xc6);
    	return 0;
}