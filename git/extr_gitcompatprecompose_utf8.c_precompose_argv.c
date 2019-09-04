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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 scalar_t__ has_non_ascii (char const*,size_t,size_t*) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_encoding ; 
 int precomposed_unicode ; 
 char* reencode_string_iconv (char const*,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_encoding ; 

void precompose_argv(int argc, const char **argv)
{
	int i = 0;
	const char *oldarg;
	char *newarg;
	iconv_t ic_precompose;

	if (precomposed_unicode != 1)
		return;

	ic_precompose = iconv_open(repo_encoding, path_encoding);
	if (ic_precompose == (iconv_t) -1)
		return;

	while (i < argc) {
		size_t namelen;
		oldarg = argv[i];
		if (has_non_ascii(oldarg, (size_t)-1, &namelen)) {
			newarg = reencode_string_iconv(oldarg, namelen, ic_precompose, 0, NULL);
			if (newarg)
				argv[i] = newarg;
		}
		i++;
	}
	iconv_close(ic_precompose);
}