#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ifmd_name; } ;
struct if_stat {char* if_name; TYPE_1__ if_mib; } ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
right_align_string(struct if_stat *ifp)
{
	int	 str_len = 0, pad_len = 0;
	char	*newstr = NULL, *ptr = NULL;

	if (ifp == NULL || ifp->if_mib.ifmd_name == NULL)
		return;
	else {
		/* string length + '\0' */
		str_len = strlen(ifp->if_mib.ifmd_name)+1;
		pad_len = IF_NAMESIZE-(str_len);

		newstr = ifp->if_name;
		ptr = newstr + pad_len;
		(void)memset((void *)newstr, (int)' ', IF_NAMESIZE);
		(void)strncpy(ptr, (const char *)&ifp->if_mib.ifmd_name,
			      str_len);
	}

	return;
}