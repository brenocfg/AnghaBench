#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int ta_fgcolor; int ta_bgcolor; } ;
typedef  TYPE_1__ teken_attr_t ;
typedef  int /*<<< orphan*/  env ;
struct TYPE_9__ {char c; TYPE_1__ a; } ;
struct TYPE_8__ {int tp_row; int tp_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_VOLATILE ; 
 scalar_t__ PTOV (scalar_t__) ; 
 int TEXT_COLS ; 
 int TEXT_ROWS ; 
 int VGA_AC_MC_BI ; 
 int VGA_AC_MC_ELG ; 
 int /*<<< orphan*/  VGA_AC_MODE_CONTROL ; 
 int /*<<< orphan*/  VGA_GEN_MISC_OUTPUT_R ; 
 int VGA_GEN_MO_IOA ; 
 scalar_t__ VGA_MEM_BASE ; 
 scalar_t__ VGA_MEM_SIZE ; 
 int /*<<< orphan*/  VGA_REG_BASE ; 
 scalar_t__ VGA_TXT_BASE ; 
 TYPE_5__* buffer ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* malloc (int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  teken ; 
 TYPE_1__* teken_get_defattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_winsize (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  tf ; 
 TYPE_2__ tp ; 
 int vga_get_atr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vga_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_set_atr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vgatext ; 
 int /*<<< orphan*/  vidc_getchar () ; 
 scalar_t__ vidc_ischar () ; 
 int /*<<< orphan*/  vidc_set_colors ; 
 int vidc_started ; 

__attribute__((used)) static int
vidc_init(int arg)
{
	const teken_attr_t *a;
	int val;
	char env[8];

	if (vidc_started && arg == 0)
		return (0);

	vidc_started = 1;

	/*
	 * Check Miscellaneous Output Register (Read at 3CCh, Write at 3C2h)
	 * for bit 1 (Input/Output Address Select), which means
	 * color/graphics adapter.
	 */
	if (vga_get_reg(VGA_REG_BASE, VGA_GEN_MISC_OUTPUT_R) & VGA_GEN_MO_IOA)
		vgatext = (uint16_t *)PTOV(VGA_TXT_BASE);
	else
		vgatext = (uint16_t *)PTOV(VGA_MEM_BASE + VGA_MEM_SIZE);

        /* set 16bit colors */
        val = vga_get_atr(VGA_REG_BASE, VGA_AC_MODE_CONTROL);
        val &= ~VGA_AC_MC_BI;
        val &= ~VGA_AC_MC_ELG;
        vga_set_atr(VGA_REG_BASE, VGA_AC_MODE_CONTROL, val);

	tp.tp_row = TEXT_ROWS;
	tp.tp_col = TEXT_COLS;
	buffer = malloc(tp.tp_row * tp.tp_col * sizeof(*buffer));
	if (buffer == NULL)
		return (1);

	snprintf(env, sizeof (env), "%u", tp.tp_row);
	setenv("LINES", env, 1);
	snprintf(env, sizeof (env), "%u", tp.tp_col);
	setenv("COLUMNS", env, 1);

	teken_init(&teken, &tf, NULL);
	teken_set_winsize(&teken, &tp);
	a = teken_get_defattr(&teken);

	snprintf(env, sizeof(env), "%d", a->ta_fgcolor);
	env_setenv("teken.fg_color", EV_VOLATILE, env, vidc_set_colors,
	    env_nounset);
	snprintf(env, sizeof(env), "%d", a->ta_bgcolor);
	env_setenv("teken.bg_color", EV_VOLATILE, env, vidc_set_colors,
	    env_nounset);

	for (int row = 0; row < tp.tp_row; row++)
		for (int col = 0; col < tp.tp_col; col++) {
			buffer[col + row * tp.tp_col].c = ' ';
			buffer[col + row * tp.tp_col].a = *a;
		}

	for (int i = 0; i < 10 && vidc_ischar(); i++)
		(void) vidc_getchar();

	return (0);	/* XXX reinit? */
}