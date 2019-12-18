#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_2__* it_v2; TYPE_1__* ot_v2; } ;
struct uaudio_terminal_node {TYPE_3__ u; } ;
struct uaudio_mixer_node {int /*<<< orphan*/  class; } ;
struct TYPE_5__ {int /*<<< orphan*/  wTerminalType; } ;
struct TYPE_4__ {int /*<<< orphan*/  wTerminalType; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_INPUT ; 
 int /*<<< orphan*/  UAC_OUTPUT ; 
 int /*<<< orphan*/  UAC_RECORD ; 
 int UAT_UNDEFINED ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 struct uaudio_terminal_node* uaudio_mixer_get_input (struct uaudio_terminal_node const*,int) ; 
 struct uaudio_terminal_node* uaudio_mixer_get_output (struct uaudio_terminal_node const*,int) ; 

__attribute__((used)) static uint16_t
uaudio20_mixer_determine_class(const struct uaudio_terminal_node *iot,
    struct uaudio_mixer_node *mix)
{
	uint16_t terminal_type = 0x0000;
	const struct uaudio_terminal_node *input[2];
	const struct uaudio_terminal_node *output[2];

	input[0] = uaudio_mixer_get_input(iot, 0);
	input[1] = uaudio_mixer_get_input(iot, 1);

	output[0] = uaudio_mixer_get_output(iot, 0);
	output[1] = uaudio_mixer_get_output(iot, 1);

	/*
	 * check if there is only
	 * one output terminal:
	 */
	if (output[0] && (!output[1]))
		terminal_type = UGETW(output[0]->u.ot_v2->wTerminalType);
	/*
	 * If the only output terminal is USB,
	 * the class is UAC_RECORD.
	 */
	if ((terminal_type & 0xff00) == (UAT_UNDEFINED & 0xff00)) {

		mix->class = UAC_RECORD;
		if (input[0] && (!input[1])) {
			terminal_type =
			    UGETW(input[0]->u.it_v2->wTerminalType);
		} else {
			terminal_type = 0;
		}
		goto done;
	}
	/*
	 * if the unit is connected to just
	 * one input terminal, the
	 * class is UAC_INPUT:
	 */
	if (input[0] && (!input[1])) {
		mix->class = UAC_INPUT;
		terminal_type =
		    UGETW(input[0]->u.it_v2->wTerminalType);
		goto done;
	}
	/*
	 * Otherwise, the class is UAC_OUTPUT.
	 */
	mix->class = UAC_OUTPUT;
done:
	return (terminal_type);
}