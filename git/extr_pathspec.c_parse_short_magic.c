#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char mnemonic; unsigned int bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int PATHSPEC_EXCLUDE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char,char const*) ; 
 int /*<<< orphan*/  is_pathspec_magic (char) ; 
 TYPE_1__* pathspec_magic ; 

__attribute__((used)) static const char *parse_short_magic(unsigned *magic, const char *elem)
{
	const char *pos;

	for (pos = elem + 1; *pos && *pos != ':'; pos++) {
		char ch = *pos;
		int i;

		/* Special case alias for '!' */
		if (ch == '^') {
			*magic |= PATHSPEC_EXCLUDE;
			continue;
		}

		if (!is_pathspec_magic(ch))
			break;

		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
			if (pathspec_magic[i].mnemonic == ch) {
				*magic |= pathspec_magic[i].bit;
				break;
			}
		}

		if (ARRAY_SIZE(pathspec_magic) <= i)
			die(_("Unimplemented pathspec magic '%c' in '%s'"),
			    ch, elem);
	}

	if (*pos == ':')
		pos++;

	return pos;
}