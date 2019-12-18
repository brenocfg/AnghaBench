#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* XkbDescPtr ;
struct TYPE_11__ {scalar_t__ available; } ;
struct TYPE_12__ {size_t* keycodes; size_t* scancodes; int /*<<< orphan*/  display; TYPE_1__ xkb; } ;
struct TYPE_16__ {TYPE_2__ x11; } ;
struct TYPE_15__ {int min_key_code; int max_key_code; TYPE_4__* names; } ;
struct TYPE_14__ {TYPE_3__* keys; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int GLFW_KEY_0 ; 
 int GLFW_KEY_1 ; 
 int GLFW_KEY_2 ; 
 int GLFW_KEY_3 ; 
 int GLFW_KEY_4 ; 
 int GLFW_KEY_5 ; 
 int GLFW_KEY_6 ; 
 int GLFW_KEY_7 ; 
 int GLFW_KEY_8 ; 
 int GLFW_KEY_9 ; 
 int GLFW_KEY_A ; 
 int GLFW_KEY_APOSTROPHE ; 
 int GLFW_KEY_B ; 
 int GLFW_KEY_BACKSLASH ; 
 int GLFW_KEY_C ; 
 int GLFW_KEY_COMMA ; 
 int GLFW_KEY_D ; 
 int GLFW_KEY_E ; 
 int GLFW_KEY_EQUAL ; 
 int GLFW_KEY_F ; 
 int GLFW_KEY_G ; 
 int GLFW_KEY_GRAVE_ACCENT ; 
 int GLFW_KEY_H ; 
 int GLFW_KEY_I ; 
 int GLFW_KEY_J ; 
 int GLFW_KEY_K ; 
 int GLFW_KEY_L ; 
 int GLFW_KEY_LEFT_BRACKET ; 
 int GLFW_KEY_M ; 
 int GLFW_KEY_MINUS ; 
 int GLFW_KEY_N ; 
 int GLFW_KEY_O ; 
 int GLFW_KEY_P ; 
 int GLFW_KEY_PERIOD ; 
 int GLFW_KEY_Q ; 
 int GLFW_KEY_R ; 
 int GLFW_KEY_RIGHT_BRACKET ; 
 int GLFW_KEY_S ; 
 int GLFW_KEY_SEMICOLON ; 
 int GLFW_KEY_SLASH ; 
 int GLFW_KEY_T ; 
 int GLFW_KEY_U ; 
 int GLFW_KEY_UNKNOWN ; 
 int GLFW_KEY_V ; 
 int GLFW_KEY_W ; 
 int GLFW_KEY_WORLD_1 ; 
 int GLFW_KEY_X ; 
 int GLFW_KEY_Y ; 
 int GLFW_KEY_Z ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XkbFreeKeyboard (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XkbFreeNames (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* XkbGetMap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XkbGetNames (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int XkbKeyNameLength ; 
 int /*<<< orphan*/  XkbKeyNamesMask ; 
 int /*<<< orphan*/  XkbUseCoreKbd ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (size_t*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int translateKeyCode (int) ; 

__attribute__((used)) static void createKeyTables(void)
{
    int scancode, key;

    memset(_glfw.x11.keycodes, -1, sizeof(_glfw.x11.keycodes));
    memset(_glfw.x11.scancodes, -1, sizeof(_glfw.x11.scancodes));

    if (_glfw.x11.xkb.available)
    {
        // Use XKB to determine physical key locations independently of the
        // current keyboard layout

        char name[XkbKeyNameLength + 1];
        XkbDescPtr desc = XkbGetMap(_glfw.x11.display, 0, XkbUseCoreKbd);
        XkbGetNames(_glfw.x11.display, XkbKeyNamesMask, desc);

        // Find the X11 key code -> GLFW key code mapping
        for (scancode = desc->min_key_code;  scancode <= desc->max_key_code;  scancode++)
        {
            memcpy(name, desc->names->keys[scancode].name, XkbKeyNameLength);
            name[XkbKeyNameLength] = '\0';

            // Map the key name to a GLFW key code. Note: We only map printable
            // keys here, and we use the US keyboard layout. The rest of the
            // keys (function keys) are mapped using traditional KeySym
            // translations.
            if (strcmp(name, "TLDE") == 0) key = GLFW_KEY_GRAVE_ACCENT;
            else if (strcmp(name, "AE01") == 0) key = GLFW_KEY_1;
            else if (strcmp(name, "AE02") == 0) key = GLFW_KEY_2;
            else if (strcmp(name, "AE03") == 0) key = GLFW_KEY_3;
            else if (strcmp(name, "AE04") == 0) key = GLFW_KEY_4;
            else if (strcmp(name, "AE05") == 0) key = GLFW_KEY_5;
            else if (strcmp(name, "AE06") == 0) key = GLFW_KEY_6;
            else if (strcmp(name, "AE07") == 0) key = GLFW_KEY_7;
            else if (strcmp(name, "AE08") == 0) key = GLFW_KEY_8;
            else if (strcmp(name, "AE09") == 0) key = GLFW_KEY_9;
            else if (strcmp(name, "AE10") == 0) key = GLFW_KEY_0;
            else if (strcmp(name, "AE11") == 0) key = GLFW_KEY_MINUS;
            else if (strcmp(name, "AE12") == 0) key = GLFW_KEY_EQUAL;
            else if (strcmp(name, "AD01") == 0) key = GLFW_KEY_Q;
            else if (strcmp(name, "AD02") == 0) key = GLFW_KEY_W;
            else if (strcmp(name, "AD03") == 0) key = GLFW_KEY_E;
            else if (strcmp(name, "AD04") == 0) key = GLFW_KEY_R;
            else if (strcmp(name, "AD05") == 0) key = GLFW_KEY_T;
            else if (strcmp(name, "AD06") == 0) key = GLFW_KEY_Y;
            else if (strcmp(name, "AD07") == 0) key = GLFW_KEY_U;
            else if (strcmp(name, "AD08") == 0) key = GLFW_KEY_I;
            else if (strcmp(name, "AD09") == 0) key = GLFW_KEY_O;
            else if (strcmp(name, "AD10") == 0) key = GLFW_KEY_P;
            else if (strcmp(name, "AD11") == 0) key = GLFW_KEY_LEFT_BRACKET;
            else if (strcmp(name, "AD12") == 0) key = GLFW_KEY_RIGHT_BRACKET;
            else if (strcmp(name, "AC01") == 0) key = GLFW_KEY_A;
            else if (strcmp(name, "AC02") == 0) key = GLFW_KEY_S;
            else if (strcmp(name, "AC03") == 0) key = GLFW_KEY_D;
            else if (strcmp(name, "AC04") == 0) key = GLFW_KEY_F;
            else if (strcmp(name, "AC05") == 0) key = GLFW_KEY_G;
            else if (strcmp(name, "AC06") == 0) key = GLFW_KEY_H;
            else if (strcmp(name, "AC07") == 0) key = GLFW_KEY_J;
            else if (strcmp(name, "AC08") == 0) key = GLFW_KEY_K;
            else if (strcmp(name, "AC09") == 0) key = GLFW_KEY_L;
            else if (strcmp(name, "AC10") == 0) key = GLFW_KEY_SEMICOLON;
            else if (strcmp(name, "AC11") == 0) key = GLFW_KEY_APOSTROPHE;
            else if (strcmp(name, "AB01") == 0) key = GLFW_KEY_Z;
            else if (strcmp(name, "AB02") == 0) key = GLFW_KEY_X;
            else if (strcmp(name, "AB03") == 0) key = GLFW_KEY_C;
            else if (strcmp(name, "AB04") == 0) key = GLFW_KEY_V;
            else if (strcmp(name, "AB05") == 0) key = GLFW_KEY_B;
            else if (strcmp(name, "AB06") == 0) key = GLFW_KEY_N;
            else if (strcmp(name, "AB07") == 0) key = GLFW_KEY_M;
            else if (strcmp(name, "AB08") == 0) key = GLFW_KEY_COMMA;
            else if (strcmp(name, "AB09") == 0) key = GLFW_KEY_PERIOD;
            else if (strcmp(name, "AB10") == 0) key = GLFW_KEY_SLASH;
            else if (strcmp(name, "BKSL") == 0) key = GLFW_KEY_BACKSLASH;
            else if (strcmp(name, "LSGT") == 0) key = GLFW_KEY_WORLD_1;
            else key = GLFW_KEY_UNKNOWN;

            if ((scancode >= 0) && (scancode < 256))
                _glfw.x11.keycodes[scancode] = key;
        }

        XkbFreeNames(desc, XkbKeyNamesMask, True);
        XkbFreeKeyboard(desc, 0, True);
    }

    for (scancode = 0;  scancode < 256;  scancode++)
    {
        // Translate the un-translated key codes using traditional X11 KeySym
        // lookups
        if (_glfw.x11.keycodes[scancode] < 0)
            _glfw.x11.keycodes[scancode] = translateKeyCode(scancode);

        // Store the reverse translation for faster key name lookup
        if (_glfw.x11.keycodes[scancode] > 0)
            _glfw.x11.scancodes[_glfw.x11.keycodes[scancode]] = scancode;
    }
}