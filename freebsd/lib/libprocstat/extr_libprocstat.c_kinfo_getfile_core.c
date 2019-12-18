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
struct procstat_core {int dummy; } ;
struct kinfo_file {scalar_t__ kf_structsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_TYPE_FILES ; 
 struct kinfo_file* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (struct kinfo_file*,struct kinfo_file*,scalar_t__) ; 
 char* procstat_core_get (struct procstat_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static struct kinfo_file *
kinfo_getfile_core(struct procstat_core *core, int *cntp)
{
	int cnt;
	size_t len;
	char *buf, *bp, *eb;
	struct kinfo_file *kif, *kp, *kf;

	buf = procstat_core_get(core, PSC_TYPE_FILES, NULL, &len);
	if (buf == NULL)
		return (NULL);
	/*
	 * XXXMG: The code below is just copy&past from libutil.
	 * The code duplication can be avoided if libutil
	 * is extended to provide something like:
	 *   struct kinfo_file *kinfo_getfile_from_buf(const char *buf,
	 *       size_t len, int *cntp);
	 */

	/* Pass 1: count items */
	cnt = 0;
	bp = buf;
	eb = buf + len;
	while (bp < eb) {
		kf = (struct kinfo_file *)(uintptr_t)bp;
		if (kf->kf_structsize == 0)
			break;
		bp += kf->kf_structsize;
		cnt++;
	}

	kif = calloc(cnt, sizeof(*kif));
	if (kif == NULL) {
		free(buf);
		return (NULL);
	}
	bp = buf;
	eb = buf + len;
	kp = kif;
	/* Pass 2: unpack */
	while (bp < eb) {
		kf = (struct kinfo_file *)(uintptr_t)bp;
		if (kf->kf_structsize == 0)
			break;
		/* Copy/expand into pre-zeroed buffer */
		memcpy(kp, kf, kf->kf_structsize);
		/* Advance to next packed record */
		bp += kf->kf_structsize;
		/* Set field size to fixed length, advance */
		kp->kf_structsize = sizeof(*kp);
		kp++;
	}
	free(buf);
	*cntp = cnt;
	return (kif);	/* Caller must free() return value */
}