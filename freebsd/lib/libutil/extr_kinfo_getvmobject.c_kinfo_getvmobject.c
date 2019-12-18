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
struct kinfo_vmobject {int kvo_structsize; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 struct kinfo_vmobject* calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (struct kinfo_vmobject*,struct kinfo_vmobject*,int) ; 
 char* reallocf (char*,size_t) ; 
 scalar_t__ sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct kinfo_vmobject *
kinfo_getvmobject(int *cntp)
{
	char *buf, *bp, *ep;
	struct kinfo_vmobject *kvo, *list, *kp;
	size_t len;
	int cnt, i;

	buf = NULL;
	for (i = 0; i < 3; i++) {
		if (sysctlbyname("vm.objects", NULL, &len, NULL, 0) < 0) {
			free(buf);
			return (NULL);
		}
		buf = reallocf(buf, len);
		if (buf == NULL)
			return (NULL);
		if (sysctlbyname("vm.objects", buf, &len, NULL, 0) == 0)
			goto unpack;
		if (errno != ENOMEM) {
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (NULL);

unpack:
	/* Count items */
	cnt = 0;
	bp = buf;
	ep = buf + len;
	while (bp < ep) {
		kvo = (struct kinfo_vmobject *)(uintptr_t)bp;
		bp += kvo->kvo_structsize;
		cnt++;
	}

	list = calloc(cnt, sizeof(*list));
	if (list == NULL) {
		free(buf);
		return (NULL);
	}

	/* Unpack */
	bp = buf;
	kp = list;
	while (bp < ep) {
		kvo = (struct kinfo_vmobject *)(uintptr_t)bp;
		memcpy(kp, kvo, kvo->kvo_structsize);
		bp += kvo->kvo_structsize;
		kp->kvo_structsize = sizeof(*kp);
		kp++;
	}
	free(buf);
	*cntp = cnt;
	return (list);
}