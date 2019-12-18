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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int SIZE_MAX ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  message_fatal (int /*<<< orphan*/ ,...) ; 
 scalar_t__* opt_block_list ; 
 scalar_t__ str_to_uint64 (char*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__* xmalloc (size_t) ; 

__attribute__((used)) static void
parse_block_list(char *str)
{
	// It must be non-empty and not begin with a comma.
	if (str[0] == '\0' || str[0] == ',')
		message_fatal(_("%s: Invalid argument to --block-list"), str);

	// Count the number of comma-separated strings.
	size_t count = 1;
	for (size_t i = 0; str[i] != '\0'; ++i)
		if (str[i] == ',')
			++count;

	// Prevent an unlikely integer overflow.
	if (count > SIZE_MAX / sizeof(uint64_t) - 1)
		message_fatal(_("%s: Too many arguments to --block-list"),
				str);

	// Allocate memory to hold all the sizes specified.
	// If --block-list was specified already, its value is forgotten.
	free(opt_block_list);
	opt_block_list = xmalloc((count + 1) * sizeof(uint64_t));

	for (size_t i = 0; i < count; ++i) {
		// Locate the next comma and replace it with \0.
		char *p = strchr(str, ',');
		if (p != NULL)
			*p = '\0';

		if (str[0] == '\0') {
			// There is no string, that is, a comma follows
			// another comma. Use the previous value.
			//
			// NOTE: We checked earler that the first char
			// of the whole list cannot be a comma.
			assert(i > 0);
			opt_block_list[i] = opt_block_list[i - 1];
		} else {
			opt_block_list[i] = str_to_uint64("block-list", str,
					0, UINT64_MAX);

			// Zero indicates no more new Blocks.
			if (opt_block_list[i] == 0) {
				if (i + 1 != count)
					message_fatal(_("0 can only be used "
							"as the last element "
							"in --block-list"));

				opt_block_list[i] = UINT64_MAX;
			}
		}

		str = p + 1;
	}

	// Terminate the array.
	opt_block_list[count] = 0;
	return;
}