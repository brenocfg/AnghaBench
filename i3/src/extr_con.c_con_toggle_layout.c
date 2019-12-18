#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ layout_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ layout; scalar_t__ last_split_layout; struct TYPE_6__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ELOG (char*,char*) ; 
 scalar_t__ L_DEFAULT ; 
 scalar_t__ L_SPLITH ; 
 scalar_t__ L_SPLITV ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 int /*<<< orphan*/  con_set_layout (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int layout_from_name (char*,scalar_t__*) ; 
 char* sstrdup (char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strstr (char const*,char const*) ; 
 char* strtok (char*,char const*) ; 

void con_toggle_layout(Con *con, const char *toggle_mode) {
    Con *parent = con;
    /* Users can focus workspaces, but not any higher in the hierarchy.
     * Focus on the workspace is a special case, since in every other case, the
     * user means "change the layout of the parent split container". */
    if (con->type != CT_WORKSPACE)
        parent = con->parent;
    DLOG("con_toggle_layout(%p, %s), parent = %p\n", con, toggle_mode, parent);

    const char delim[] = " ";

    if (strcasecmp(toggle_mode, "split") == 0 || strstr(toggle_mode, delim)) {
        /* L_DEFAULT is used as a placeholder value to distinguish if
         * the first layout has already been saved. (it can never be L_DEFAULT) */
        layout_t new_layout = L_DEFAULT;
        bool current_layout_found = false;
        char *tm_dup = sstrdup(toggle_mode);
        char *cur_tok = strtok(tm_dup, delim);

        for (layout_t layout; cur_tok != NULL; cur_tok = strtok(NULL, delim)) {
            if (strcasecmp(cur_tok, "split") == 0) {
                /* Toggle between splits. When the current layout is not a split
                 * layout, we just switch back to last_split_layout. Otherwise, we
                 * change to the opposite split layout. */
                if (parent->layout != L_SPLITH && parent->layout != L_SPLITV) {
                    layout = parent->last_split_layout;
                    /* In case last_split_layout was not initialized… */
                    if (layout == L_DEFAULT) {
                        layout = L_SPLITH;
                    }
                } else {
                    layout = (parent->layout == L_SPLITH) ? L_SPLITV : L_SPLITH;
                }
            } else {
                bool success = layout_from_name(cur_tok, &layout);
                if (!success || layout == L_DEFAULT) {
                    ELOG("The token '%s' was not recognized and has been skipped.\n", cur_tok);
                    continue;
                }
            }

            /* If none of the specified layouts match the current,
             * fall back to the first layout in the list */
            if (new_layout == L_DEFAULT) {
                new_layout = layout;
            }

            /* We found the active layout in the last iteration, so
             * now let's activate the current layout (next in list) */
            if (current_layout_found) {
                new_layout = layout;
                break;
            }

            if (parent->layout == layout) {
                current_layout_found = true;
            }
        }
        free(tm_dup);

        if (new_layout != L_DEFAULT) {
            con_set_layout(con, new_layout);
        }
    } else if (strcasecmp(toggle_mode, "all") == 0 || strcasecmp(toggle_mode, "default") == 0) {
        if (parent->layout == L_STACKED)
            con_set_layout(con, L_TABBED);
        else if (parent->layout == L_TABBED) {
            if (strcasecmp(toggle_mode, "all") == 0)
                con_set_layout(con, L_SPLITH);
            else
                con_set_layout(con, parent->last_split_layout);
        } else if (parent->layout == L_SPLITH || parent->layout == L_SPLITV) {
            if (strcasecmp(toggle_mode, "all") == 0) {
                /* When toggling through all modes, we toggle between
                 * splith/splitv, whereas normally we just directly jump to
                 * stacked. */
                if (parent->layout == L_SPLITH)
                    con_set_layout(con, L_SPLITV);
                else
                    con_set_layout(con, L_STACKED);
            } else {
                con_set_layout(con, L_STACKED);
            }
        }
    }
}