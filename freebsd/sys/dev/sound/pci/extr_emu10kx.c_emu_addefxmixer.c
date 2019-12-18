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
typedef  int /*<<< orphan*/  uint32_t ;
struct emu_sc_info {int /*<<< orphan*/  root; int /*<<< orphan*/  ctx; int /*<<< orphan*/  rm; } ;

/* Variables and functions */
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct emu_sc_info*,int const,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int emu_rm_gpr_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emumix_set_fxvol (struct emu_sc_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  sysctl_emu_mixer_control ; 

__attribute__((used)) static int
emu_addefxmixer(struct emu_sc_info *sc, const char *mix_name, const int mix_id, uint32_t defvolume)
{
	int volgpr;
	char	sysctl_name[32];

	volgpr = emu_rm_gpr_alloc(sc->rm, 1);
	emumix_set_fxvol(sc, volgpr, defvolume);
	/*
	 * Mixer controls with NULL mix_name are handled
	 * by AC97 emulation code or PCM mixer.
	 */
	if (mix_name != NULL) {
		/*
		 * Temporary sysctls should start with underscore,
		 * see freebsd-current mailing list, emu10kx driver
		 * discussion around 2006-05-24.
		 */
		snprintf(sysctl_name, 32, "_%s", mix_name);
		SYSCTL_ADD_PROC(sc->ctx,
			SYSCTL_CHILDREN(sc->root),
			OID_AUTO, sysctl_name,
			CTLTYPE_INT | CTLFLAG_RW, sc, mix_id,
			sysctl_emu_mixer_control, "I", "");
	}

	return (volgpr);
}