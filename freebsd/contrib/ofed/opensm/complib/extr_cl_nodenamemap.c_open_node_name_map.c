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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  nn_map_t ;

/* Variables and functions */
 scalar_t__ EIO ; 
 char* HAVE_DEFAULT_NODENAME_MAP ; 
 int PARSE_NODE_MAP_BUFLEN ; 
 int /*<<< orphan*/  cl_qmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_node_name_map (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  map_name ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ parse_node_map_wrap (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 

nn_map_t *open_node_name_map(const char *node_name_map)
{
	nn_map_t *map;
	char linebuf[PARSE_NODE_MAP_BUFLEN + 1];

	if (!node_name_map) {
#ifdef HAVE_DEFAULT_NODENAME_MAP
		struct stat buf;
		node_name_map = HAVE_DEFAULT_NODENAME_MAP;
		if (stat(node_name_map, &buf))
			return NULL;
#else
		return NULL;
#endif				/* HAVE_DEFAULT_NODENAME_MAP */
	}

	map = malloc(sizeof(*map));
	if (!map)
		return NULL;
	cl_qmap_init(map);

	memset(linebuf, '\0', PARSE_NODE_MAP_BUFLEN + 1);
	if (parse_node_map_wrap(node_name_map, map_name, map,
				linebuf, PARSE_NODE_MAP_BUFLEN)) {
		if (errno == EIO) {
			fprintf(stderr,
				"WARNING failed to parse node name map "
				"\"%s\"\n",
				node_name_map);
			fprintf(stderr,
				"WARNING failed line: \"%s\"\n",
				linebuf);
		}
		else
			fprintf(stderr,
				"WARNING failed to open node name map "
				"\"%s\" (%s)\n",
				node_name_map, strerror(errno));
		close_node_name_map(map);
		return NULL;
	}

	return map;
}