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
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_sprom_layout ;

/* Variables and functions */
 int BHND_NVRAM_DATA_PROBE_DEFAULT ; 
 int bhnd_nvram_sprom_ident (struct bhnd_nvram_io*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_probe(struct bhnd_nvram_io *io)
{
	const bhnd_sprom_layout	*layout;
	int			 error;

	/* Try to parse the input */
	if ((error = bhnd_nvram_sprom_ident(io, &layout)))
		return (error);

	return (BHND_NVRAM_DATA_PROBE_DEFAULT);
}