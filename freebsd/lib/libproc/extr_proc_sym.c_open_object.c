#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {char* pr_mapname; } ;
struct map_info {TYPE_1__ map; struct file_info* file; } ;
struct file_info {int fd; int /*<<< orphan*/ * elf; int /*<<< orphan*/  ehdr; } ;
typedef  TYPE_1__ prmap_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  crc ;
struct TYPE_9__ {int d_size; char* d_buf; } ;
struct TYPE_8__ {scalar_t__ sh_type; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_3__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,char*) ; 
 int /*<<< orphan*/  DPRINTFX (char*,...) ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 char* PATH_DEBUG_DIR ; 
 int PATH_MAX ; 
 scalar_t__ SHT_PROGBITS ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dirname (char*) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int elf_errmsg (int) ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ elf_getshdrstrndx (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  load_symtabs (struct file_info*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int open (char*,int) ; 
 int open_debug_file (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static int
open_object(struct map_info *mapping)
{
	char path[PATH_MAX];
	GElf_Shdr shdr;
	Elf *e, *e2;
	Elf_Data *data;
	Elf_Scn *scn;
	struct file_info *file;
	prmap_t *map;
	const char *debugfile, *scnname;
	size_t ndx;
	uint32_t crc;
	int fd, fd2;

	if (mapping->map.pr_mapname[0] == '\0')
		return (-1); /* anonymous object */
	if (mapping->file->elf != NULL)
		return (0); /* already loaded */

	file = mapping->file;
	map = &mapping->map;
	if ((fd = open(map->pr_mapname, O_RDONLY | O_CLOEXEC)) < 0) {
		DPRINTF("ERROR: open %s failed", map->pr_mapname);
		return (-1);
	}
	if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
		DPRINTFX("ERROR: elf_begin() failed: %s", elf_errmsg(-1));
		goto err;
	}
	if (gelf_getehdr(e, &file->ehdr) != &file->ehdr) {
		DPRINTFX("ERROR: elf_getehdr() failed: %s", elf_errmsg(-1));
		goto err;
	}

	scn = NULL;
	while ((scn = elf_nextscn(e, scn)) != NULL) {
		if (gelf_getshdr(scn, &shdr) != &shdr) {
			DPRINTFX("ERROR: gelf_getshdr failed: %s",
			    elf_errmsg(-1));
			goto err;
		}
		if (shdr.sh_type != SHT_PROGBITS)
			continue;
		if (elf_getshdrstrndx(e, &ndx) != 0) {
			DPRINTFX("ERROR: elf_getshdrstrndx failed: %s",
			    elf_errmsg(-1));
			goto err;
		}
		if ((scnname = elf_strptr(e, ndx, shdr.sh_name)) == NULL)
			continue;

		if (strcmp(scnname, ".gnu_debuglink") == 0)
			break;
	}
	if (scn == NULL)
		goto internal;

	if ((data = elf_getdata(scn, NULL)) == NULL) {
		DPRINTFX("ERROR: elf_getdata failed: %s", elf_errmsg(-1));
		goto err;
	}

	/*
	 * The data contains a null-terminated file name followed by a 4-byte
	 * CRC.
	 */
	if (data->d_size < sizeof(crc) + 1) {
		DPRINTFX("ERROR: debuglink section is too small (%zd bytes)",
		    data->d_size);
		goto internal;
	}
	if (strnlen(data->d_buf, data->d_size) >= data->d_size - sizeof(crc)) {
		DPRINTFX("ERROR: no null-terminator in gnu_debuglink section");
		goto internal;
	}

	debugfile = data->d_buf;
	memcpy(&crc, (char *)data->d_buf + data->d_size - sizeof(crc),
	    sizeof(crc));

	/*
	 * Search for the debug file using the algorithm described in the gdb
	 * documentation:
	 * - look in the directory containing the object,
	 * - look in the subdirectory ".debug" of the directory containing the
	 *   object,
	 * - look in the global debug directories (currently /usr/lib/debug).
	 */
	(void)strlcpy(path, map->pr_mapname, sizeof(path));
	(void)dirname(path);

	if ((fd2 = open_debug_file(path, debugfile, crc)) >= 0)
		goto external;

	if (strlcat(path, "/.debug", sizeof(path)) < sizeof(path) &&
	    (fd2 = open_debug_file(path, debugfile, crc)) >= 0)
		goto external;

	(void)snprintf(path, sizeof(path), PATH_DEBUG_DIR);
	if (strlcat(path, map->pr_mapname, sizeof(path)) < sizeof(path)) {
		(void)dirname(path);
		if ((fd2 = open_debug_file(path, debugfile, crc)) >= 0)
			goto external;
	}

internal:
	/* We didn't find a debug file, just return the object's descriptor. */
	file->elf = e;
	file->fd = fd;
	load_symtabs(file);
	return (0);

external:
	if ((e2 = elf_begin(fd2, ELF_C_READ, NULL)) == NULL) {
		DPRINTFX("ERROR: elf_begin failed: %s", elf_errmsg(-1));
		(void)close(fd2);
		goto err;
	}
	(void)elf_end(e);
	(void)close(fd);
	file->elf = e2;
	file->fd = fd2;
	load_symtabs(file);
	return (0);

err:
	if (e != NULL)
		(void)elf_end(e);
	(void)close(fd);
	return (-1);
}