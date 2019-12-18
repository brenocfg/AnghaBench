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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  add_count (int /*<<< orphan*/ ,int) ; 
 char const* bufbeg ; 
 scalar_t__ color_option ; 
 int /*<<< orphan*/  dossified_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t execute (char const*,int,size_t*,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* filename ; 
 int filename_mask ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ ) ; 
 char* grep_color ; 
 char const* lastnl ; 
 char const* lastout ; 
 scalar_t__ line_buffered ; 
 int /*<<< orphan*/  nlscan (char const*) ; 
 scalar_t__ only_matching ; 
 scalar_t__ out_byte ; 
 scalar_t__ out_file ; 
 scalar_t__ out_line ; 
 int /*<<< orphan*/  print_offset_sep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 size_t stub1 (char const*,int,size_t*,int) ; 
 size_t stub2 (char const*,int,size_t*,int) ; 
 int /*<<< orphan*/  totalcc ; 
 int /*<<< orphan*/  totalnl ; 

__attribute__((used)) static void
prline (char const *beg, char const *lim, int sep)
{
  if (out_file)
    printf ("%s%c", filename, sep & filename_mask);
  if (out_line)
    {
      nlscan (beg);
      totalnl = add_count (totalnl, 1);
      print_offset_sep (totalnl, sep);
      lastnl = lim;
    }
  if (out_byte)
    {
      uintmax_t pos = add_count (totalcc, beg - bufbeg);
#if defined(HAVE_DOS_FILE_CONTENTS)
      pos = dossified_pos (pos);
#endif
      print_offset_sep (pos, sep);
    }
  if (only_matching)
    {
      size_t match_size;
      size_t match_offset;
      while ((match_offset = (*execute) (beg, lim - beg, &match_size, 1))
	  != (size_t) -1)
        {
	  char const *b = beg + match_offset;
	  if (b == lim)
	    break;
	  if (match_size == 0)
	    break;
	  if(color_option)
	    printf("\33[%sm", grep_color);
	  fwrite(b, sizeof (char), match_size, stdout);
	  if(color_option)
	    fputs("\33[00m", stdout);
	  fputs("\n", stdout);
	  beg = b + match_size;
        }
      lastout = lim;
      if(line_buffered)
	fflush(stdout);
      return;
    }
  if (color_option)
    {
      size_t match_size;
      size_t match_offset;
      while (lim-beg && (match_offset = (*execute) (beg, lim - beg, &match_size, 1))
	     != (size_t) -1)
	{
	  char const *b = beg + match_offset;
	  /* Avoid matching the empty line at the end of the buffer. */
	  if (b == lim)
	    break;
	  /* Avoid hanging on grep --color "" foo */
	  if (match_size == 0)
	    break;
	  fwrite (beg, sizeof (char), match_offset, stdout);
	  printf ("\33[%sm", grep_color);
	  fwrite (b, sizeof (char), match_size, stdout);
	  fputs ("\33[00m", stdout);
	  beg = b + match_size;
	}
      fputs ("\33[K", stdout);
    }
  fwrite (beg, 1, lim - beg, stdout);
  if (ferror (stdout))
    error (0, errno, _("writing output"));
  lastout = lim;
  if (line_buffered)
    fflush (stdout);
}