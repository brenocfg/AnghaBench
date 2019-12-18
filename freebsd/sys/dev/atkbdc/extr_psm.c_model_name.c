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

/* Variables and functions */
#define  MOUSE_MODEL_4D 142 
#define  MOUSE_MODEL_4DPLUS 141 
#define  MOUSE_MODEL_ELANTECH 140 
#define  MOUSE_MODEL_EXPLORER 139 
#define  MOUSE_MODEL_GENERIC 138 
#define  MOUSE_MODEL_GLIDEPOINT 137 
#define  MOUSE_MODEL_INTELLI 136 
#define  MOUSE_MODEL_MOUSEMANPLUS 135 
#define  MOUSE_MODEL_NET 134 
#define  MOUSE_MODEL_NETSCROLL 133 
#define  MOUSE_MODEL_SYNAPTICS 132 
#define  MOUSE_MODEL_THINK 131 
#define  MOUSE_MODEL_TRACKPOINT 130 
#define  MOUSE_MODEL_UNKNOWN 129 
#define  MOUSE_MODEL_VERSAPAD 128 

__attribute__((used)) static char *
model_name(int model)
{
	static struct {
		int	model_code;
		char	*model_name;
	} models[] = {
		{ MOUSE_MODEL_NETSCROLL,	"NetScroll" },
		{ MOUSE_MODEL_NET,		"NetMouse/NetScroll Optical" },
		{ MOUSE_MODEL_GLIDEPOINT,	"GlidePoint" },
		{ MOUSE_MODEL_THINK,		"ThinkingMouse" },
		{ MOUSE_MODEL_INTELLI,		"IntelliMouse" },
		{ MOUSE_MODEL_MOUSEMANPLUS,	"MouseMan+" },
		{ MOUSE_MODEL_VERSAPAD,		"VersaPad" },
		{ MOUSE_MODEL_EXPLORER,		"IntelliMouse Explorer" },
		{ MOUSE_MODEL_4D,		"4D Mouse" },
		{ MOUSE_MODEL_4DPLUS,		"4D+ Mouse" },
		{ MOUSE_MODEL_SYNAPTICS,	"Synaptics Touchpad" },
		{ MOUSE_MODEL_TRACKPOINT,	"IBM/Lenovo TrackPoint" },
		{ MOUSE_MODEL_ELANTECH,		"Elantech Touchpad" },
		{ MOUSE_MODEL_GENERIC,		"Generic PS/2 mouse" },
		{ MOUSE_MODEL_UNKNOWN,		"Unknown" },
	};
	int i;

	for (i = 0; models[i].model_code != MOUSE_MODEL_UNKNOWN; ++i)
		if (models[i].model_code == model)
			break;
	return (models[i].model_name);
}