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

/* Variables and functions */
 unsigned int A_BOLD ; 
 int BUTTON1_RELEASED ; 
 int BUTTON4_PRESSED ; 
 int BUTTON5_PRESSED ; 
 int /*<<< orphan*/  Black ; 
 int /*<<< orphan*/  CODESET ; 
 size_t COLORSCHEME_BROKENGRAY ; 
 size_t COLORSCHEME_DEFAULT ; 
 int CRT_colorScheme ; 
 unsigned int** CRT_colorSchemes ; 
 unsigned int* CRT_colors ; 
 int CRT_delay ; 
 int /*<<< orphan*/  CRT_handleSIGSEGV ; 
 int /*<<< orphan*/  CRT_handleSIGTERM ; 
 int CRT_hasColors ; 
 int CRT_scrollHAmount ; 
 int /*<<< orphan*/  CRT_setColors (int) ; 
 int /*<<< orphan*/  CRT_termType ; 
 int /*<<< orphan*/  CRT_treeStr ; 
 int /*<<< orphan*/  CRT_treeStrAscii ; 
 int /*<<< orphan*/  CRT_treeStrUtf8 ; 
 int CRT_utf8 ; 
 unsigned int ColorPair (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ColorPairGrayBlack ; 
 int /*<<< orphan*/  KEY_ALT (char) ; 
 int /*<<< orphan*/  KEY_END ; 
 int /*<<< orphan*/  KEY_F (int) ; 
 int /*<<< orphan*/  KEY_HOME ; 
 int LAST_COLORELEMENT ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int SIGQUIT ; 
 int SIGTERM ; 
 scalar_t__ String_eq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ String_startsWith (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  White ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_key (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  halfdelay (int) ; 
 scalar_t__ has_colors () ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  intrflush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mouseinterval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousemask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  stdscr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  use_default_colors () ; 

void CRT_init(int delay, int colorScheme) {
   initscr();
   noecho();
   CRT_delay = delay;
   if (CRT_delay == 0) {
      CRT_delay = 1;
   }
   CRT_colors = CRT_colorSchemes[colorScheme];
   CRT_colorScheme = colorScheme;
   
   for (int i = 0; i < LAST_COLORELEMENT; i++) {
      unsigned int color = CRT_colorSchemes[COLORSCHEME_DEFAULT][i];
      CRT_colorSchemes[COLORSCHEME_BROKENGRAY][i] = color == (A_BOLD | ColorPairGrayBlack) ? ColorPair(White,Black) : color;
   }
   
   halfdelay(CRT_delay);
   nonl();
   intrflush(stdscr, false);
   keypad(stdscr, true);
   mouseinterval(0);
   curs_set(0);
   if (has_colors()) {
      start_color();
      CRT_hasColors = true;
   } else {
      CRT_hasColors = false;
   }
   CRT_termType = getenv("TERM");
   if (String_eq(CRT_termType, "linux"))
      CRT_scrollHAmount = 20;
   else
      CRT_scrollHAmount = 5;
   if (String_startsWith(CRT_termType, "xterm") || String_eq(CRT_termType, "vt220")) {
      define_key("\033[H", KEY_HOME);
      define_key("\033[F", KEY_END);
      define_key("\033[7~", KEY_HOME);
      define_key("\033[8~", KEY_END);
      define_key("\033OP", KEY_F(1));
      define_key("\033OQ", KEY_F(2));
      define_key("\033OR", KEY_F(3));
      define_key("\033OS", KEY_F(4));
      define_key("\033[11~", KEY_F(1));
      define_key("\033[12~", KEY_F(2));
      define_key("\033[13~", KEY_F(3));
      define_key("\033[14~", KEY_F(4));
      define_key("\033[17;2~", KEY_F(18));
      char sequence[3] = "\033a";
      for (char c = 'a'; c <= 'z'; c++) {
         sequence[1] = c;
         define_key(sequence, KEY_ALT('A' + (c - 'a')));
      }
   }
#ifndef DEBUG
   signal(11, CRT_handleSIGSEGV);
#endif
   signal(SIGTERM, CRT_handleSIGTERM);
   signal(SIGQUIT, CRT_handleSIGTERM);
   use_default_colors();
   if (!has_colors())
      CRT_colorScheme = 1;
   CRT_setColors(CRT_colorScheme);

   /* initialize locale */
   setlocale(LC_CTYPE, "");

#ifdef HAVE_LIBNCURSESW
   if(strcmp(nl_langinfo(CODESET), "UTF-8") == 0)
      CRT_utf8 = true;
   else
      CRT_utf8 = false;
#endif

   CRT_treeStr =
#ifdef HAVE_LIBNCURSESW
      CRT_utf8 ? CRT_treeStrUtf8 :
#endif
      CRT_treeStrAscii;

#if NCURSES_MOUSE_VERSION > 1
   mousemask(BUTTON1_RELEASED | BUTTON4_PRESSED | BUTTON5_PRESSED, NULL);
#else
   mousemask(BUTTON1_RELEASED, NULL);
#endif

}