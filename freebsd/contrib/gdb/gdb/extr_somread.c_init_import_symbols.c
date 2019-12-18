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
struct objfile {char** import_list; unsigned int import_list_size; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  asection ;
typedef  char* ImportEntry ;

/* Variables and functions */
 int SOM_READ_IMPORTS_CHUNK_SIZE ; 
 int SOM_READ_IMPORTS_NUM ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (unsigned int) ; 

__attribute__((used)) static int
init_import_symbols (struct objfile *objfile)
{
  unsigned int import_list;
  unsigned int import_list_size;
  unsigned int string_table;
  unsigned int string_table_size;
  char *string_buffer;
  int i;
  int j;
  int k;
  asection *text_section;	/* section handle */
  unsigned int dl_header[12];	/* SOM executable header */

  /* A struct for an entry in the SOM import list */
  typedef struct
    {
      int name;			/* index into the string table */
      short dont_care1;		/* we don't use this */
      unsigned char type;	/* 0 = NULL, 2 = Data, 3 = Code, 7 = Storage, 13 = Plabel */
      unsigned int reserved2:8;	/* not used */
    }
  SomImportEntry;

  /* We read 100 entries in at a time from the disk file. */
#define SOM_READ_IMPORTS_NUM         100
#define SOM_READ_IMPORTS_CHUNK_SIZE  (sizeof (SomImportEntry) * SOM_READ_IMPORTS_NUM)
  SomImportEntry buffer[SOM_READ_IMPORTS_NUM];

  /* Initialize in case we error out */
  objfile->import_list = NULL;
  objfile->import_list_size = 0;

  /* It doesn't work, for some reason, to read in space $TEXT$;
     the subspace $SHLIB_INFO$ has to be used.  Some BFD quirk? pai/1997-08-05 */
  text_section = bfd_get_section_by_name (objfile->obfd, "$SHLIB_INFO$");
  if (!text_section)
    return 0;
  /* Get the SOM executable header */
  bfd_get_section_contents (objfile->obfd, text_section, dl_header, 0, 12 * sizeof (int));

  /* Check header version number for 10.x HP-UX */
  /* Currently we deal only with 10.x systems; on 9.x the version # is 89060912.
     FIXME: Change for future HP-UX releases and mods to the SOM executable format */
  if (dl_header[0] != 93092112)
    return 0;

  import_list = dl_header[4];
  import_list_size = dl_header[5];
  if (!import_list_size)
    return 0;
  string_table = dl_header[10];
  string_table_size = dl_header[11];
  if (!string_table_size)
    return 0;

  /* Suck in SOM string table */
  string_buffer = (char *) xmalloc (string_table_size);
  bfd_get_section_contents (objfile->obfd, text_section, string_buffer,
			    string_table, string_table_size);

  /* Allocate import list in the psymbol obstack; this has nothing
     to do with psymbols, just a matter of convenience.  We want the
     import list to be freed when the objfile is deallocated */
  objfile->import_list
    = (ImportEntry *) obstack_alloc (&objfile->objfile_obstack,
				   import_list_size * sizeof (ImportEntry));

  /* Read in the import entries, a bunch at a time */
  for (j = 0, k = 0;
       j < (import_list_size / SOM_READ_IMPORTS_NUM);
       j++)
    {
      bfd_get_section_contents (objfile->obfd, text_section, buffer,
			      import_list + j * SOM_READ_IMPORTS_CHUNK_SIZE,
				SOM_READ_IMPORTS_CHUNK_SIZE);
      for (i = 0; i < SOM_READ_IMPORTS_NUM; i++, k++)
	{
	  if (buffer[i].type != (unsigned char) 0)
	    {
	      objfile->import_list[k]
		= (char *) obstack_alloc (&objfile->objfile_obstack, strlen (string_buffer + buffer[i].name) + 1);
	      strcpy (objfile->import_list[k], string_buffer + buffer[i].name);
	      /* Some day we might want to record the type and other information too */
	    }
	  else			/* null type */
	    objfile->import_list[k] = NULL;

	}
    }

  /* Get the leftovers */
  if (k < import_list_size)
    bfd_get_section_contents (objfile->obfd, text_section, buffer,
			      import_list + k * sizeof (SomImportEntry),
			  (import_list_size - k) * sizeof (SomImportEntry));
  for (i = 0; k < import_list_size; i++, k++)
    {
      if (buffer[i].type != (unsigned char) 0)
	{
	  objfile->import_list[k]
	    = (char *) obstack_alloc (&objfile->objfile_obstack, strlen (string_buffer + buffer[i].name) + 1);
	  strcpy (objfile->import_list[k], string_buffer + buffer[i].name);
	  /* Some day we might want to record the type and other information too */
	}
      else
	objfile->import_list[k] = NULL;
    }

  objfile->import_list_size = import_list_size;
  xfree (string_buffer);
  return import_list_size;
}