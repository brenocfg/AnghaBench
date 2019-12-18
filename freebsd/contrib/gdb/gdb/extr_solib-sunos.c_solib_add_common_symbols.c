#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rtc_symb {int /*<<< orphan*/  rtc_next; int /*<<< orphan*/  rtc_sp; } ;
struct TYPE_6__ {int n_strx; int /*<<< orphan*/  n_name; } ;
struct nlist {scalar_t__ n_type; int n_value; TYPE_1__ n_un; } ;
typedef  int /*<<< orphan*/  inferior_rtc_symb ;
typedef  int /*<<< orphan*/  inferior_rtc_nlist ;
struct TYPE_7__ {int /*<<< orphan*/ * msymbols; scalar_t__ minimal_symbol_count; int /*<<< orphan*/  objfile_obstack; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ N_COMM ; 
 scalar_t__ SOLIB_EXTRACT_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_rt_common_objfile () ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int /*<<< orphan*/  install_minimal_symbols (TYPE_2__*) ; 
 int /*<<< orphan*/  make_cleanup_discard_minimal_symbols () ; 
 int /*<<< orphan*/  mst_bss ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prim_record_minimal_symbol (char*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int) ; 
 TYPE_2__* rt_common_objfile ; 
 int /*<<< orphan*/  terminate_minimal_symbol_table (TYPE_2__*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
solib_add_common_symbols (CORE_ADDR rtc_symp)
{
  struct rtc_symb inferior_rtc_symb;
  struct nlist inferior_rtc_nlist;
  int len;
  char *name;

  /* Remove any runtime common symbols from previous runs.  */

  if (rt_common_objfile != NULL && rt_common_objfile->minimal_symbol_count)
    {
      obstack_free (&rt_common_objfile->objfile_obstack, 0);
      obstack_init (&rt_common_objfile->objfile_obstack);
      rt_common_objfile->minimal_symbol_count = 0;
      rt_common_objfile->msymbols = NULL;
      terminate_minimal_symbol_table (rt_common_objfile);
    }

  init_minimal_symbol_collection ();
  make_cleanup_discard_minimal_symbols ();

  while (rtc_symp)
    {
      read_memory (rtc_symp,
		   (char *) &inferior_rtc_symb,
		   sizeof (inferior_rtc_symb));
      read_memory (SOLIB_EXTRACT_ADDRESS (inferior_rtc_symb.rtc_sp),
		   (char *) &inferior_rtc_nlist,
		   sizeof (inferior_rtc_nlist));
      if (inferior_rtc_nlist.n_type == N_COMM)
	{
	  /* FIXME: The length of the symbol name is not available, but in the
	     current implementation the common symbol is allocated immediately
	     behind the name of the symbol. */
	  len = inferior_rtc_nlist.n_value - inferior_rtc_nlist.n_un.n_strx;

	  name = xmalloc (len);
	  read_memory (SOLIB_EXTRACT_ADDRESS (inferior_rtc_nlist.n_un.n_name),
		       name, len);

	  /* Allocate the runtime common objfile if necessary. */
	  if (rt_common_objfile == NULL)
	    allocate_rt_common_objfile ();

	  prim_record_minimal_symbol (name, inferior_rtc_nlist.n_value,
				      mst_bss, rt_common_objfile);
	  xfree (name);
	}
      rtc_symp = SOLIB_EXTRACT_ADDRESS (inferior_rtc_symb.rtc_next);
    }

  /* Install any minimal symbols that have been collected as the current
     minimal symbols for the runtime common objfile.  */

  install_minimal_symbols (rt_common_objfile);
}