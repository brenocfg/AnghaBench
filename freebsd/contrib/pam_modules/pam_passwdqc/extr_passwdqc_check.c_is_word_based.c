#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int match_length; } ;
typedef  TYPE_1__ passwdqc_params_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _passwdqc_wordset_4k ; 
 int /*<<< orphan*/  clean (char*) ; 
 scalar_t__ is_based (TYPE_1__*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 char* unify (char*) ; 

__attribute__((used)) static int is_word_based(passwdqc_params_t *params,
    const char *needle, const char *original)
{
	char word[7];
	char *unified;
	int i;

	word[6] = '\0';
	for (i = 0; i < 0x1000; i++) {
		memcpy(word, _passwdqc_wordset_4k[i], 6);
		if ((int)strlen(word) < params->match_length) continue;
		unified = unify(word);
		if (is_based(params, unified, needle, original)) {
			clean(unified);
			return 1;
		}
		clean(unified);
	}

	return 0;
}