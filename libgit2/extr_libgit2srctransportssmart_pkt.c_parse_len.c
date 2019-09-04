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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int GIT_EBUFS ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int PKT_LEN_SIZE ; 
 int git__strntol32 (scalar_t__*,char*,int,char const**,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int parse_len(size_t *out, const char *line, size_t linelen)
{
	char num[PKT_LEN_SIZE + 1];
	int i, k, error;
	int32_t len;
	const char *num_end;

	/* Not even enough for the length */
	if (linelen < PKT_LEN_SIZE)
		return GIT_EBUFS;

	memcpy(num, line, PKT_LEN_SIZE);
	num[PKT_LEN_SIZE] = '\0';

	for (i = 0; i < PKT_LEN_SIZE; ++i) {
		if (!isxdigit(num[i])) {
			/* Make sure there are no special characters before passing to error message */
			for (k = 0; k < PKT_LEN_SIZE; ++k) {
				if(!isprint(num[k])) {
					num[k] = '.';
				}
			}

			git_error_set(GIT_ERROR_NET, "invalid hex digit in length: '%s'", num);
			return -1;
		}
	}

	if ((error = git__strntol32(&len, num, PKT_LEN_SIZE, &num_end, 16)) < 0)
		return error;

	if (len < 0)
		return -1;

	*out = (size_t) len;
	return 0;
}