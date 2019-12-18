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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int EEXIST ; 
 int kiconv_add_xlat_table (char const*,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  smb_error (char*,int,char const*,char const*) ; 

__attribute__((used)) static int
smb_addiconvtbl(const char *to, const char *from, const u_char *tbl)
{
	int error;

	error = kiconv_add_xlat_table(to, from, tbl);
	if (error && error != EEXIST) {
		smb_error("can not setup kernel iconv table (%s:%s)", error,
		    from, to);
		return error;
	}
	return 0;
}