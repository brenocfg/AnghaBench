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
typedef  int xkb_keysym_t ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_3__ {scalar_t__ next_state; } ;
typedef  TYPE_1__ cmdp_token ;
typedef  scalar_t__ cmdp_state ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 scalar_t__ __CALL ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  clear_stack () ; 
 int /*<<< orphan*/  errx (int,char*,int const) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_string (char*) ; 
 int /*<<< orphan*/  keysym_used_on_other_key (int const,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char*,char*,char*,char*,char*) ; 
 char* sstrdup (char const*) ; 
 scalar_t__ state ; 
 scalar_t__* statelist ; 
 int statelist_idx ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 int /*<<< orphan*/  xkb_keymap ; 
 int xkb_keymap_key_get_syms_by_level (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int const**) ; 
 int xkb_keysym_get_name (int const,char*,int) ; 

__attribute__((used)) static char *next_state(const cmdp_token *token) {
    cmdp_state _next_state = token->next_state;

    if (token->next_state == __CALL) {
        const char *modifiers = get_string("modifiers");
        int keycode = atoi(get_string("key"));
        int level = 0;
        if (modifiers != NULL &&
            strstr(modifiers, "Shift") != NULL) {
            /* When shift is included, we really need to use the second-level
             * symbol (upper-case). The lower-case symbol could be on a
             * different key than the upper-case one (unlikely for letters, but
             * more likely for special characters). */
            level = 1;

            /* Try to use the keysym on the first level (lower-case). In case
             * this doesn’t make it ambiguous (think of a keyboard layout
             * having '1' on two different keys, but '!' only on keycode 10),
             * we’ll stick with the keysym of the first level.
             *
             * This reduces a lot of confusion for users who switch keyboard
             * layouts from qwerty to qwertz or other slight variations of
             * qwerty (yes, that happens quite often). */
            const xkb_keysym_t *syms;
            int num = xkb_keymap_key_get_syms_by_level(xkb_keymap, keycode, 0, 0, &syms);
            if (num == 0)
                errx(1, "xkb_keymap_key_get_syms_by_level returned no symbols for keycode %d", keycode);
            if (!keysym_used_on_other_key(syms[0], keycode))
                level = 0;
        }

        const xkb_keysym_t *syms;
        int num = xkb_keymap_key_get_syms_by_level(xkb_keymap, keycode, 0, level, &syms);
        if (num == 0)
            errx(1, "xkb_keymap_key_get_syms_by_level returned no symbols for keycode %d", keycode);
        if (num > 1)
            printf("xkb_keymap_key_get_syms_by_level (keycode = %d) returned %d symbolsinstead of 1, using only the first one.\n", keycode, num);

        char str[4096];
        if (xkb_keysym_get_name(syms[0], str, sizeof(str)) == -1)
            errx(EXIT_FAILURE, "xkb_keysym_get_name(%u) failed", syms[0]);
        const char *release = get_string("release");
        char *res;
        char *modrep = (modifiers == NULL ? sstrdup("") : sstrdup(modifiers));
        char *comma;
        while ((comma = strchr(modrep, ',')) != NULL) {
            *comma = '+';
        }
        sasprintf(&res, "bindsym %s%s%s %s%s\n", (modifiers == NULL ? "" : modrep), (modifiers == NULL ? "" : "+"), str, (release == NULL ? "" : release), get_string("command"));
        clear_stack();
        free(modrep);
        return res;
    }

    state = _next_state;

    /* See if we are jumping back to a state in which we were in previously
     * (statelist contains INITIAL) and just move statelist_idx accordingly. */
    for (int i = 0; i < statelist_idx; i++) {
        if (statelist[i] != _next_state)
            continue;
        statelist_idx = i + 1;
        return NULL;
    }

    /* Otherwise, the state is new and we add it to the list */
    statelist[statelist_idx++] = _next_state;
    return NULL;
}