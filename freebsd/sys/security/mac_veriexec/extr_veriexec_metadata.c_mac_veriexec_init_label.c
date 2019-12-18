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
 int /*<<< orphan*/  M_VERIEXEC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ve_mutex ; 

__attribute__((used)) static size_t
mac_veriexec_init_label(char **labelp, size_t labellen, char *src,
    size_t srclen)
{
	char *label;

	label = *labelp;
	if (labellen < srclen) {
		mtx_unlock(&ve_mutex);
		if (label != NULL)
			free(label, M_VERIEXEC);
		label = malloc(srclen, M_VERIEXEC, M_WAITOK);
		mtx_lock(&ve_mutex);
		labellen = srclen;
		*labelp = label;
	}
	memcpy(label, src, srclen);
	return labellen;
}