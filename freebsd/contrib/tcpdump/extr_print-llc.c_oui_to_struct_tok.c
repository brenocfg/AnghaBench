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
typedef  scalar_t__ uint32_t ;
struct tok {int dummy; } ;
struct oui_tok {scalar_t__ oui; struct tok* tok; } ;

/* Variables and functions */
 struct tok* null_values ; 
 struct oui_tok* oui_to_tok ; 

__attribute__((used)) static const struct tok *
oui_to_struct_tok(uint32_t orgcode)
{
	const struct tok *tok = null_values;
	const struct oui_tok *otp;

	for (otp = &oui_to_tok[0]; otp->tok != NULL; otp++) {
		if (otp->oui == orgcode) {
			tok = otp->tok;
			break;
		}
	}
	return (tok);
}