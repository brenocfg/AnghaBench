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
struct test_entry {char* key; } ;
struct strbuf {int /*<<< orphan*/ * buf; } ;
struct hashmap_iter {int dummy; } ;
struct hashmap_entry {int dummy; } ;
struct hashmap {int tablesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELIM ; 
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 struct test_entry* alloc_test_entry (unsigned int,char*,char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  free (struct test_entry*) ; 
 char* get_value (struct test_entry*) ; 
 int /*<<< orphan*/  hashmap_add (struct hashmap*,struct test_entry*) ; 
 int /*<<< orphan*/  hashmap_entry_init (struct hashmap_entry*,unsigned int) ; 
 int /*<<< orphan*/  hashmap_free (struct hashmap*,int) ; 
 struct test_entry* hashmap_get_from_hash (struct hashmap*,unsigned int,char*) ; 
 struct test_entry* hashmap_get_next (struct hashmap*,struct test_entry*) ; 
 int hashmap_get_size (struct hashmap*) ; 
 int /*<<< orphan*/  hashmap_init (struct hashmap*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct test_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 struct test_entry* hashmap_put (struct hashmap*,struct test_entry*) ; 
 struct test_entry* hashmap_remove (struct hashmap*,struct hashmap_entry*,char*) ; 
 int memhash (char*,int /*<<< orphan*/ ) ; 
 int memihash (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_hashmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strhash (char*) ; 
 int strihash (char*) ; 
 char* strintern (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strtok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_entry_cmp ; 

int cmd__hashmap(int argc, const char **argv)
{
	struct strbuf line = STRBUF_INIT;
	struct hashmap map;
	int icase;

	/* init hash map */
	icase = argc > 1 && !strcmp("ignorecase", argv[1]);
	hashmap_init(&map, test_entry_cmp, &icase, 0);

	/* process commands from stdin */
	while (strbuf_getline(&line, stdin) != EOF) {
		char *cmd, *p1 = NULL, *p2 = NULL;
		unsigned int hash = 0;
		struct test_entry *entry;

		/* break line into command and up to two parameters */
		cmd = strtok(line.buf, DELIM);
		/* ignore empty lines */
		if (!cmd || *cmd == '#')
			continue;

		p1 = strtok(NULL, DELIM);
		if (p1) {
			hash = icase ? strihash(p1) : strhash(p1);
			p2 = strtok(NULL, DELIM);
		}

		if (!strcmp("hash", cmd) && p1) {

			/* print results of different hash functions */
			printf("%u %u %u %u\n",
			       strhash(p1), memhash(p1, strlen(p1)),
			       strihash(p1), memihash(p1, strlen(p1)));

		} else if (!strcmp("add", cmd) && p1 && p2) {

			/* create entry with key = p1, value = p2 */
			entry = alloc_test_entry(hash, p1, p2);

			/* add to hashmap */
			hashmap_add(&map, entry);

		} else if (!strcmp("put", cmd) && p1 && p2) {

			/* create entry with key = p1, value = p2 */
			entry = alloc_test_entry(hash, p1, p2);

			/* add / replace entry */
			entry = hashmap_put(&map, entry);

			/* print and free replaced entry, if any */
			puts(entry ? get_value(entry) : "NULL");
			free(entry);

		} else if (!strcmp("get", cmd) && p1) {

			/* lookup entry in hashmap */
			entry = hashmap_get_from_hash(&map, hash, p1);

			/* print result */
			if (!entry)
				puts("NULL");
			while (entry) {
				puts(get_value(entry));
				entry = hashmap_get_next(&map, entry);
			}

		} else if (!strcmp("remove", cmd) && p1) {

			/* setup static key */
			struct hashmap_entry key;
			hashmap_entry_init(&key, hash);

			/* remove entry from hashmap */
			entry = hashmap_remove(&map, &key, p1);

			/* print result and free entry*/
			puts(entry ? get_value(entry) : "NULL");
			free(entry);

		} else if (!strcmp("iterate", cmd)) {

			struct hashmap_iter iter;
			hashmap_iter_init(&map, &iter);
			while ((entry = hashmap_iter_next(&iter)))
				printf("%s %s\n", entry->key, get_value(entry));

		} else if (!strcmp("size", cmd)) {

			/* print table sizes */
			printf("%u %u\n", map.tablesize,
			       hashmap_get_size(&map));

		} else if (!strcmp("intern", cmd) && p1) {

			/* test that strintern works */
			const char *i1 = strintern(p1);
			const char *i2 = strintern(p1);
			if (strcmp(i1, p1))
				printf("strintern(%s) returns %s\n", p1, i1);
			else if (i1 == p1)
				printf("strintern(%s) returns input pointer\n", p1);
			else if (i1 != i2)
				printf("strintern(%s) != strintern(%s)", i1, i2);
			else
				printf("%s\n", i1);

		} else if (!strcmp("perfhashmap", cmd) && p1 && p2) {

			perf_hashmap(atoi(p1), atoi(p2));

		} else {

			printf("Unknown command %s\n", cmd);

		}
	}

	strbuf_release(&line);
	hashmap_free(&map, 1);
	return 0;
}