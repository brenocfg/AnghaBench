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
typedef  int ssize_t ;
typedef  scalar_t__ const_efidp ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int MAXSIZE ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int efidp_format_device_path (char*,int,scalar_t__,size_t) ; 
 size_t efidp_size (scalar_t__) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read_file (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void
format(void)
{
	char buffer[MAXSIZE];
	ssize_t fmtlen;
	ssize_t len;
	void *data;
	size_t dplen;
	const_efidp dp;

	len = read_file(STDIN_FILENO, &data);
	if (len == -1)
		err(1, "read");
	dp = (const_efidp)data;
	while (len > 0) {
		dplen = efidp_size(dp);
		fmtlen = efidp_format_device_path(buffer, sizeof(buffer),
		    dp, dplen);
		if (fmtlen > 0)
			printf("%s\n", buffer);
		len -= dplen;
		dp = (const_efidp)((const char *)dp + dplen);
	}
	free(data);
}