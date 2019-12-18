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
struct bhnd_nvram_tlv {int dummy; } ;
struct bhnd_nvram_io {int dummy; } ;
struct bhnd_nvram_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nvram_tlv_free (struct bhnd_nvram_data*) ; 
 int bhnd_nvram_tlv_init (struct bhnd_nvram_tlv*,struct bhnd_nvram_io*) ; 

__attribute__((used)) static int
bhnd_nvram_tlv_new(struct bhnd_nvram_data *nv, struct bhnd_nvram_io *io)
{
	
	struct bhnd_nvram_tlv	*tlv;
	int			 error;

	/* Allocate and initialize the TLV data instance */
	tlv = (struct bhnd_nvram_tlv *)nv;

	/* Parse the TLV input data and initialize our backing
	 * data representation */
	if ((error = bhnd_nvram_tlv_init(tlv, io))) {
		bhnd_nvram_tlv_free(nv);
		return (error);
	}

	return (0);
}