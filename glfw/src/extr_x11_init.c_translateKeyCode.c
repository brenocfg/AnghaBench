#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  group; scalar_t__ available; } ;
struct TYPE_5__ {int /*<<< orphan*/  display; TYPE_1__ xkb; } ;
struct TYPE_6__ {TYPE_2__ x11; } ;
typedef  int KeySym ;

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
 int GLFW_KEY_BACKSPACE ; 
 int GLFW_KEY_C ; 
 int GLFW_KEY_CAPS_LOCK ; 
 int GLFW_KEY_COMMA ; 
 int GLFW_KEY_D ; 
 int GLFW_KEY_DELETE ; 
 int GLFW_KEY_DOWN ; 
 int GLFW_KEY_E ; 
 int GLFW_KEY_END ; 
 int GLFW_KEY_ENTER ; 
 int GLFW_KEY_EQUAL ; 
 int GLFW_KEY_ESCAPE ; 
 int GLFW_KEY_F ; 
 int GLFW_KEY_F1 ; 
 int GLFW_KEY_F10 ; 
 int GLFW_KEY_F11 ; 
 int GLFW_KEY_F12 ; 
 int GLFW_KEY_F13 ; 
 int GLFW_KEY_F14 ; 
 int GLFW_KEY_F15 ; 
 int GLFW_KEY_F16 ; 
 int GLFW_KEY_F17 ; 
 int GLFW_KEY_F18 ; 
 int GLFW_KEY_F19 ; 
 int GLFW_KEY_F2 ; 
 int GLFW_KEY_F20 ; 
 int GLFW_KEY_F21 ; 
 int GLFW_KEY_F22 ; 
 int GLFW_KEY_F23 ; 
 int GLFW_KEY_F24 ; 
 int GLFW_KEY_F25 ; 
 int GLFW_KEY_F3 ; 
 int GLFW_KEY_F4 ; 
 int GLFW_KEY_F5 ; 
 int GLFW_KEY_F6 ; 
 int GLFW_KEY_F7 ; 
 int GLFW_KEY_F8 ; 
 int GLFW_KEY_F9 ; 
 int GLFW_KEY_G ; 
 int GLFW_KEY_GRAVE_ACCENT ; 
 int GLFW_KEY_H ; 
 int GLFW_KEY_HOME ; 
 int GLFW_KEY_I ; 
 int GLFW_KEY_INSERT ; 
 int GLFW_KEY_J ; 
 int GLFW_KEY_K ; 
 int GLFW_KEY_KP_0 ; 
 int GLFW_KEY_KP_1 ; 
 int GLFW_KEY_KP_2 ; 
 int GLFW_KEY_KP_3 ; 
 int GLFW_KEY_KP_4 ; 
 int GLFW_KEY_KP_5 ; 
 int GLFW_KEY_KP_6 ; 
 int GLFW_KEY_KP_7 ; 
 int GLFW_KEY_KP_8 ; 
 int GLFW_KEY_KP_9 ; 
 int GLFW_KEY_KP_ADD ; 
 int GLFW_KEY_KP_DECIMAL ; 
 int GLFW_KEY_KP_DIVIDE ; 
 int GLFW_KEY_KP_ENTER ; 
 int GLFW_KEY_KP_EQUAL ; 
 int GLFW_KEY_KP_MULTIPLY ; 
 int GLFW_KEY_KP_SUBTRACT ; 
 int GLFW_KEY_L ; 
 int GLFW_KEY_LEFT ; 
 int GLFW_KEY_LEFT_ALT ; 
 int GLFW_KEY_LEFT_BRACKET ; 
 int GLFW_KEY_LEFT_CONTROL ; 
 int GLFW_KEY_LEFT_SHIFT ; 
 int GLFW_KEY_LEFT_SUPER ; 
 int GLFW_KEY_M ; 
 int GLFW_KEY_MENU ; 
 int GLFW_KEY_MINUS ; 
 int GLFW_KEY_N ; 
 int GLFW_KEY_NUM_LOCK ; 
 int GLFW_KEY_O ; 
 int GLFW_KEY_P ; 
 int GLFW_KEY_PAGE_DOWN ; 
 int GLFW_KEY_PAGE_UP ; 
 int GLFW_KEY_PAUSE ; 
 int GLFW_KEY_PERIOD ; 
 int GLFW_KEY_PRINT_SCREEN ; 
 int GLFW_KEY_Q ; 
 int GLFW_KEY_R ; 
 int GLFW_KEY_RIGHT ; 
 int GLFW_KEY_RIGHT_ALT ; 
 int GLFW_KEY_RIGHT_BRACKET ; 
 int GLFW_KEY_RIGHT_CONTROL ; 
 int GLFW_KEY_RIGHT_SHIFT ; 
 int GLFW_KEY_RIGHT_SUPER ; 
 int GLFW_KEY_S ; 
 int GLFW_KEY_SCROLL_LOCK ; 
 int GLFW_KEY_SEMICOLON ; 
 int GLFW_KEY_SLASH ; 
 int GLFW_KEY_SPACE ; 
 int GLFW_KEY_T ; 
 int GLFW_KEY_TAB ; 
 int GLFW_KEY_U ; 
 int GLFW_KEY_UNKNOWN ; 
 int GLFW_KEY_UP ; 
 int GLFW_KEY_V ; 
 int GLFW_KEY_W ; 
 int GLFW_KEY_WORLD_1 ; 
 int GLFW_KEY_X ; 
 int GLFW_KEY_Y ; 
 int GLFW_KEY_Z ; 
 int /*<<< orphan*/  XFree (int*) ; 
 int* XGetKeyboardMapping (int /*<<< orphan*/ ,int,int,int*) ; 
#define  XK_0 261 
#define  XK_1 260 
#define  XK_2 259 
#define  XK_3 258 
#define  XK_4 257 
#define  XK_5 256 
#define  XK_6 255 
#define  XK_7 254 
#define  XK_8 253 
#define  XK_9 252 
#define  XK_Alt_L 251 
#define  XK_Alt_R 250 
#define  XK_BackSpace 249 
#define  XK_Caps_Lock 248 
#define  XK_Control_L 247 
#define  XK_Control_R 246 
#define  XK_Delete 245 
#define  XK_Down 244 
#define  XK_End 243 
#define  XK_Escape 242 
#define  XK_F1 241 
#define  XK_F10 240 
#define  XK_F11 239 
#define  XK_F12 238 
#define  XK_F13 237 
#define  XK_F14 236 
#define  XK_F15 235 
#define  XK_F16 234 
#define  XK_F17 233 
#define  XK_F18 232 
#define  XK_F19 231 
#define  XK_F2 230 
#define  XK_F20 229 
#define  XK_F21 228 
#define  XK_F22 227 
#define  XK_F23 226 
#define  XK_F24 225 
#define  XK_F25 224 
#define  XK_F3 223 
#define  XK_F4 222 
#define  XK_F5 221 
#define  XK_F6 220 
#define  XK_F7 219 
#define  XK_F8 218 
#define  XK_F9 217 
#define  XK_Home 216 
#define  XK_ISO_Level3_Shift 215 
#define  XK_Insert 214 
#define  XK_KP_0 213 
#define  XK_KP_1 212 
#define  XK_KP_2 211 
#define  XK_KP_3 210 
#define  XK_KP_4 209 
#define  XK_KP_5 208 
#define  XK_KP_6 207 
#define  XK_KP_7 206 
#define  XK_KP_8 205 
#define  XK_KP_9 204 
#define  XK_KP_Add 203 
#define  XK_KP_Decimal 202 
#define  XK_KP_Delete 201 
#define  XK_KP_Divide 200 
#define  XK_KP_Down 199 
#define  XK_KP_End 198 
#define  XK_KP_Enter 197 
#define  XK_KP_Equal 196 
#define  XK_KP_Home 195 
#define  XK_KP_Insert 194 
#define  XK_KP_Left 193 
#define  XK_KP_Multiply 192 
#define  XK_KP_Page_Down 191 
#define  XK_KP_Page_Up 190 
#define  XK_KP_Right 189 
#define  XK_KP_Separator 188 
#define  XK_KP_Subtract 187 
#define  XK_KP_Up 186 
#define  XK_Left 185 
#define  XK_Menu 184 
#define  XK_Meta_L 183 
#define  XK_Meta_R 182 
#define  XK_Mode_switch 181 
#define  XK_Num_Lock 180 
#define  XK_Page_Down 179 
#define  XK_Page_Up 178 
#define  XK_Pause 177 
#define  XK_Print 176 
#define  XK_Return 175 
#define  XK_Right 174 
#define  XK_Scroll_Lock 173 
#define  XK_Shift_L 172 
#define  XK_Shift_R 171 
#define  XK_Super_L 170 
#define  XK_Super_R 169 
#define  XK_Tab 168 
#define  XK_Up 167 
#define  XK_a 166 
#define  XK_apostrophe 165 
#define  XK_b 164 
#define  XK_backslash 163 
#define  XK_bracketleft 162 
#define  XK_bracketright 161 
#define  XK_c 160 
#define  XK_comma 159 
#define  XK_d 158 
#define  XK_e 157 
#define  XK_equal 156 
#define  XK_f 155 
#define  XK_g 154 
#define  XK_grave 153 
#define  XK_h 152 
#define  XK_i 151 
#define  XK_j 150 
#define  XK_k 149 
#define  XK_l 148 
#define  XK_less 147 
#define  XK_m 146 
#define  XK_minus 145 
#define  XK_n 144 
#define  XK_o 143 
#define  XK_p 142 
#define  XK_period 141 
#define  XK_q 140 
#define  XK_r 139 
#define  XK_s 138 
#define  XK_semicolon 137 
#define  XK_slash 136 
#define  XK_space 135 
#define  XK_t 134 
#define  XK_u 133 
#define  XK_v 132 
#define  XK_w 131 
#define  XK_x 130 
#define  XK_y 129 
#define  XK_z 128 
 int XkbKeycodeToKeysym (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ _glfw ; 

__attribute__((used)) static int translateKeyCode(int scancode)
{
    int keySym;

    // Valid key code range is  [8,255], according to the Xlib manual
    if (scancode < 8 || scancode > 255)
        return GLFW_KEY_UNKNOWN;

    if (_glfw.x11.xkb.available)
    {
        // Try secondary keysym, for numeric keypad keys
        // Note: This way we always force "NumLock = ON", which is intentional
        // since the returned key code should correspond to a physical
        // location.
        keySym = XkbKeycodeToKeysym(_glfw.x11.display, scancode, _glfw.x11.xkb.group, 1);
        switch (keySym)
        {
            case XK_KP_0:           return GLFW_KEY_KP_0;
            case XK_KP_1:           return GLFW_KEY_KP_1;
            case XK_KP_2:           return GLFW_KEY_KP_2;
            case XK_KP_3:           return GLFW_KEY_KP_3;
            case XK_KP_4:           return GLFW_KEY_KP_4;
            case XK_KP_5:           return GLFW_KEY_KP_5;
            case XK_KP_6:           return GLFW_KEY_KP_6;
            case XK_KP_7:           return GLFW_KEY_KP_7;
            case XK_KP_8:           return GLFW_KEY_KP_8;
            case XK_KP_9:           return GLFW_KEY_KP_9;
            case XK_KP_Separator:
            case XK_KP_Decimal:     return GLFW_KEY_KP_DECIMAL;
            case XK_KP_Equal:       return GLFW_KEY_KP_EQUAL;
            case XK_KP_Enter:       return GLFW_KEY_KP_ENTER;
            default:                break;
        }

        // Now try primary keysym for function keys (non-printable keys)
        // These should not depend on the current keyboard layout
        keySym = XkbKeycodeToKeysym(_glfw.x11.display, scancode, _glfw.x11.xkb.group, 0);
    }
    else
    {
        int dummy;
        KeySym* keySyms;

        keySyms = XGetKeyboardMapping(_glfw.x11.display, scancode, 1, &dummy);
        keySym = keySyms[0];
        XFree(keySyms);
    }

    switch (keySym)
    {
        case XK_Escape:         return GLFW_KEY_ESCAPE;
        case XK_Tab:            return GLFW_KEY_TAB;
        case XK_Shift_L:        return GLFW_KEY_LEFT_SHIFT;
        case XK_Shift_R:        return GLFW_KEY_RIGHT_SHIFT;
        case XK_Control_L:      return GLFW_KEY_LEFT_CONTROL;
        case XK_Control_R:      return GLFW_KEY_RIGHT_CONTROL;
        case XK_Meta_L:
        case XK_Alt_L:          return GLFW_KEY_LEFT_ALT;
        case XK_Mode_switch: // Mapped to Alt_R on many keyboards
        case XK_ISO_Level3_Shift: // AltGr on at least some machines
        case XK_Meta_R:
        case XK_Alt_R:          return GLFW_KEY_RIGHT_ALT;
        case XK_Super_L:        return GLFW_KEY_LEFT_SUPER;
        case XK_Super_R:        return GLFW_KEY_RIGHT_SUPER;
        case XK_Menu:           return GLFW_KEY_MENU;
        case XK_Num_Lock:       return GLFW_KEY_NUM_LOCK;
        case XK_Caps_Lock:      return GLFW_KEY_CAPS_LOCK;
        case XK_Print:          return GLFW_KEY_PRINT_SCREEN;
        case XK_Scroll_Lock:    return GLFW_KEY_SCROLL_LOCK;
        case XK_Pause:          return GLFW_KEY_PAUSE;
        case XK_Delete:         return GLFW_KEY_DELETE;
        case XK_BackSpace:      return GLFW_KEY_BACKSPACE;
        case XK_Return:         return GLFW_KEY_ENTER;
        case XK_Home:           return GLFW_KEY_HOME;
        case XK_End:            return GLFW_KEY_END;
        case XK_Page_Up:        return GLFW_KEY_PAGE_UP;
        case XK_Page_Down:      return GLFW_KEY_PAGE_DOWN;
        case XK_Insert:         return GLFW_KEY_INSERT;
        case XK_Left:           return GLFW_KEY_LEFT;
        case XK_Right:          return GLFW_KEY_RIGHT;
        case XK_Down:           return GLFW_KEY_DOWN;
        case XK_Up:             return GLFW_KEY_UP;
        case XK_F1:             return GLFW_KEY_F1;
        case XK_F2:             return GLFW_KEY_F2;
        case XK_F3:             return GLFW_KEY_F3;
        case XK_F4:             return GLFW_KEY_F4;
        case XK_F5:             return GLFW_KEY_F5;
        case XK_F6:             return GLFW_KEY_F6;
        case XK_F7:             return GLFW_KEY_F7;
        case XK_F8:             return GLFW_KEY_F8;
        case XK_F9:             return GLFW_KEY_F9;
        case XK_F10:            return GLFW_KEY_F10;
        case XK_F11:            return GLFW_KEY_F11;
        case XK_F12:            return GLFW_KEY_F12;
        case XK_F13:            return GLFW_KEY_F13;
        case XK_F14:            return GLFW_KEY_F14;
        case XK_F15:            return GLFW_KEY_F15;
        case XK_F16:            return GLFW_KEY_F16;
        case XK_F17:            return GLFW_KEY_F17;
        case XK_F18:            return GLFW_KEY_F18;
        case XK_F19:            return GLFW_KEY_F19;
        case XK_F20:            return GLFW_KEY_F20;
        case XK_F21:            return GLFW_KEY_F21;
        case XK_F22:            return GLFW_KEY_F22;
        case XK_F23:            return GLFW_KEY_F23;
        case XK_F24:            return GLFW_KEY_F24;
        case XK_F25:            return GLFW_KEY_F25;

        // Numeric keypad
        case XK_KP_Divide:      return GLFW_KEY_KP_DIVIDE;
        case XK_KP_Multiply:    return GLFW_KEY_KP_MULTIPLY;
        case XK_KP_Subtract:    return GLFW_KEY_KP_SUBTRACT;
        case XK_KP_Add:         return GLFW_KEY_KP_ADD;

        // These should have been detected in secondary keysym test above!
        case XK_KP_Insert:      return GLFW_KEY_KP_0;
        case XK_KP_End:         return GLFW_KEY_KP_1;
        case XK_KP_Down:        return GLFW_KEY_KP_2;
        case XK_KP_Page_Down:   return GLFW_KEY_KP_3;
        case XK_KP_Left:        return GLFW_KEY_KP_4;
        case XK_KP_Right:       return GLFW_KEY_KP_6;
        case XK_KP_Home:        return GLFW_KEY_KP_7;
        case XK_KP_Up:          return GLFW_KEY_KP_8;
        case XK_KP_Page_Up:     return GLFW_KEY_KP_9;
        case XK_KP_Delete:      return GLFW_KEY_KP_DECIMAL;
        case XK_KP_Equal:       return GLFW_KEY_KP_EQUAL;
        case XK_KP_Enter:       return GLFW_KEY_KP_ENTER;

        // Last resort: Check for printable keys (should not happen if the XKB
        // extension is available). This will give a layout dependent mapping
        // (which is wrong, and we may miss some keys, especially on non-US
        // keyboards), but it's better than nothing...
        case XK_a:              return GLFW_KEY_A;
        case XK_b:              return GLFW_KEY_B;
        case XK_c:              return GLFW_KEY_C;
        case XK_d:              return GLFW_KEY_D;
        case XK_e:              return GLFW_KEY_E;
        case XK_f:              return GLFW_KEY_F;
        case XK_g:              return GLFW_KEY_G;
        case XK_h:              return GLFW_KEY_H;
        case XK_i:              return GLFW_KEY_I;
        case XK_j:              return GLFW_KEY_J;
        case XK_k:              return GLFW_KEY_K;
        case XK_l:              return GLFW_KEY_L;
        case XK_m:              return GLFW_KEY_M;
        case XK_n:              return GLFW_KEY_N;
        case XK_o:              return GLFW_KEY_O;
        case XK_p:              return GLFW_KEY_P;
        case XK_q:              return GLFW_KEY_Q;
        case XK_r:              return GLFW_KEY_R;
        case XK_s:              return GLFW_KEY_S;
        case XK_t:              return GLFW_KEY_T;
        case XK_u:              return GLFW_KEY_U;
        case XK_v:              return GLFW_KEY_V;
        case XK_w:              return GLFW_KEY_W;
        case XK_x:              return GLFW_KEY_X;
        case XK_y:              return GLFW_KEY_Y;
        case XK_z:              return GLFW_KEY_Z;
        case XK_1:              return GLFW_KEY_1;
        case XK_2:              return GLFW_KEY_2;
        case XK_3:              return GLFW_KEY_3;
        case XK_4:              return GLFW_KEY_4;
        case XK_5:              return GLFW_KEY_5;
        case XK_6:              return GLFW_KEY_6;
        case XK_7:              return GLFW_KEY_7;
        case XK_8:              return GLFW_KEY_8;
        case XK_9:              return GLFW_KEY_9;
        case XK_0:              return GLFW_KEY_0;
        case XK_space:          return GLFW_KEY_SPACE;
        case XK_minus:          return GLFW_KEY_MINUS;
        case XK_equal:          return GLFW_KEY_EQUAL;
        case XK_bracketleft:    return GLFW_KEY_LEFT_BRACKET;
        case XK_bracketright:   return GLFW_KEY_RIGHT_BRACKET;
        case XK_backslash:      return GLFW_KEY_BACKSLASH;
        case XK_semicolon:      return GLFW_KEY_SEMICOLON;
        case XK_apostrophe:     return GLFW_KEY_APOSTROPHE;
        case XK_grave:          return GLFW_KEY_GRAVE_ACCENT;
        case XK_comma:          return GLFW_KEY_COMMA;
        case XK_period:         return GLFW_KEY_PERIOD;
        case XK_slash:          return GLFW_KEY_SLASH;
        case XK_less:           return GLFW_KEY_WORLD_1; // At least in some layouts...
        default:                break;
    }

    // No matching translation was found
    return GLFW_KEY_UNKNOWN;
}