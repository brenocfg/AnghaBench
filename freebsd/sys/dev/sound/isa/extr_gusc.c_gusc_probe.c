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
typedef  int u_int32_t ;
struct sndcard_func {int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  LOGICALID_MIDI 130 
#define  LOGICALID_OPL 129 
#define  LOGICALID_PCM 128 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SCF_MIDI ; 
 int /*<<< orphan*/  SCF_PCM ; 
 int /*<<< orphan*/  SCF_SYNTH ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct sndcard_func*) ; 
 int /*<<< orphan*/  gusc_ids ; 
 int gusisa_probe (int /*<<< orphan*/ ) ; 
 int isa_get_logicalid (int /*<<< orphan*/ ) ; 
 struct sndcard_func* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
gusc_probe(device_t dev)
{
	device_t child;
	u_int32_t logical_id;
	char *s;
	struct sndcard_func *func;
	int ret;

	logical_id = isa_get_logicalid(dev);
	s = NULL;

	/* Check isapnp ids */
	if (logical_id != 0 && (ret = ISA_PNP_PROBE(device_get_parent(dev), dev, gusc_ids)) != 0)
		return (ret);
	else {
		if (logical_id == 0)
			return gusisa_probe(dev);
	}

	switch (logical_id) {
	case LOGICALID_PCM:
		s = "Gravis UltraSound Plug & Play PCM";
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL)
			return (ENOMEM);
		func->func = SCF_PCM;
		child = device_add_child(dev, "pcm", -1);
		device_set_ivars(child, func);
		break;
	case LOGICALID_OPL:
		s = "Gravis UltraSound Plug & Play OPL";
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL)
			return (ENOMEM);
		func->func = SCF_SYNTH;
		child = device_add_child(dev, "midi", -1);
		device_set_ivars(child, func);
		break;
	case LOGICALID_MIDI:
		s = "Gravis UltraSound Plug & Play MIDI";
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL)
			return (ENOMEM);
		func->func = SCF_MIDI;
		child = device_add_child(dev, "midi", -1);
		device_set_ivars(child, func);
		break;
	}

	if (s != NULL) {
		device_set_desc(dev, s);
		return (0);
	}

	return (ENXIO);
}