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
typedef  int /*<<< orphan*/  u_int ;
struct fpn {int dummy; } ;
struct fpemu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FPE_REG ; 
#define  FTYPE_DBL 131 
#define  FTYPE_INT 130 
#define  FTYPE_LNG 129 
#define  FTYPE_SNG 128 
 int /*<<< orphan*/  fpu_ftod (struct fpemu*,struct fpn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpu_ftoi (struct fpemu*,struct fpn*) ; 
 int /*<<< orphan*/  fpu_ftos (struct fpemu*,struct fpn*) ; 
 int /*<<< orphan*/  fpu_ftox (struct fpemu*,struct fpn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
fpu_implode(struct fpemu *fe, struct fpn *fp, int type, u_int *space)
{

	switch (type) {

	case FTYPE_LNG:
		space[0] = fpu_ftox(fe, fp, space);
		DPRINTF(FPE_REG, ("fpu_implode: long %x %x\n",
			space[0], space[1]));
		break;

	case FTYPE_INT:
		space[0] = 0;
		space[1] = fpu_ftoi(fe, fp);
		DPRINTF(FPE_REG, ("fpu_implode: int %x\n",
			space[1]));
		break;

	case FTYPE_SNG:
		space[0] = fpu_ftos(fe, fp);
		DPRINTF(FPE_REG, ("fpu_implode: single %x\n",
			space[0]));
		break;

	case FTYPE_DBL:
		space[0] = fpu_ftod(fe, fp, space);
		DPRINTF(FPE_REG, ("fpu_implode: double %x %x\n",
			space[0], space[1]));
		break;		break;

	default:
		panic("fpu_implode: invalid type %d", type);
	}
}