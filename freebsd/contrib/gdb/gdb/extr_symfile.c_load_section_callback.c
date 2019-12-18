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
struct load_section_data {scalar_t__ load_offset; int data_count; int write_count; int /*<<< orphan*/  total_size; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int SEC_LOAD ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_size (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_lma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ download_write_size ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 char const* paddr (scalar_t__) ; 
 int /*<<< orphan*/  paddr_nz (scalar_t__) ; 
 scalar_t__ quit_flag ; 
 int /*<<< orphan*/  show_load_progress (char const*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ target_read_memory (scalar_t__,char*,int) ; 
 int target_write_memory_partial (scalar_t__,char*,scalar_t__,int*) ; 
 scalar_t__ ui_load_progress_hook (char const*,scalar_t__) ; 
 int /*<<< orphan*/  ui_out_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 scalar_t__ validate_download ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
load_section_callback (bfd *abfd, asection *asec, void *data)
{
  struct load_section_data *args = data;

  if (bfd_get_section_flags (abfd, asec) & SEC_LOAD)
    {
      bfd_size_type size = bfd_get_section_size (asec);
      if (size > 0)
	{
	  char *buffer;
	  struct cleanup *old_chain;
	  CORE_ADDR lma = bfd_section_lma (abfd, asec) + args->load_offset;
	  bfd_size_type block_size;
	  int err;
	  const char *sect_name = bfd_get_section_name (abfd, asec);
	  bfd_size_type sent;

	  if (download_write_size > 0 && size > download_write_size)
	    block_size = download_write_size;
	  else
	    block_size = size;

	  buffer = xmalloc (size);
	  old_chain = make_cleanup (xfree, buffer);

	  /* Is this really necessary?  I guess it gives the user something
	     to look at during a long download.  */
	  ui_out_message (uiout, 0, "Loading section %s, size 0x%s lma 0x%s\n",
			  sect_name, paddr_nz (size), paddr_nz (lma));

	  bfd_get_section_contents (abfd, asec, buffer, 0, size);

	  sent = 0;
	  do
	    {
	      int len;
	      bfd_size_type this_transfer = size - sent;

	      if (this_transfer >= block_size)
		this_transfer = block_size;
	      len = target_write_memory_partial (lma, buffer,
						 this_transfer, &err);
	      if (err)
		break;
	      if (validate_download)
		{
		  /* Broken memories and broken monitors manifest
		     themselves here when bring new computers to
		     life.  This doubles already slow downloads.  */
		  /* NOTE: cagney/1999-10-18: A more efficient
		     implementation might add a verify_memory()
		     method to the target vector and then use
		     that.  remote.c could implement that method
		     using the ``qCRC'' packet.  */
		  char *check = xmalloc (len);
		  struct cleanup *verify_cleanups = 
		    make_cleanup (xfree, check);

		  if (target_read_memory (lma, check, len) != 0)
		    error ("Download verify read failed at 0x%s",
			   paddr (lma));
		  if (memcmp (buffer, check, len) != 0)
		    error ("Download verify compare failed at 0x%s",
			   paddr (lma));
		  do_cleanups (verify_cleanups);
		}
	      args->data_count += len;
	      lma += len;
	      buffer += len;
	      args->write_count += 1;
	      sent += len;
	      if (quit_flag
		  || (ui_load_progress_hook != NULL
		      && ui_load_progress_hook (sect_name, sent)))
		error ("Canceled the download");

	      if (show_load_progress != NULL)
		show_load_progress (sect_name, sent, size, 
				    args->data_count, args->total_size);
	    }
	  while (sent < size);

	  if (err != 0)
	    error ("Memory access error while loading section %s.", sect_name);

	  do_cleanups (old_chain);
	}
    }
}