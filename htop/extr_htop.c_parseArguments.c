#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; char member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {int userId; int sortKey; int delay; int useColors; int treeView; int /*<<< orphan*/ * pidWhiteList; } ;
typedef  TYPE_1__ CommandLineSettings ;

/* Variables and functions */
 int /*<<< orphan*/  Action_setUserOnly (char*,int*) ; 
 int ColumnsPanel_fieldNameToIndex (char*) ; 
 int EOF ; 
 int /*<<< orphan*/ * Hashtable_new (int,int) ; 
 int /*<<< orphan*/  Hashtable_put (int /*<<< orphan*/ *,unsigned int,void*) ; 
 int Platform_numberOfFields ; 
 TYPE_3__* Process_fields ; 
 unsigned int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
#define  no_argument 129 
 char* optarg ; 
 int /*<<< orphan*/  printHelpFlag () ; 
 int /*<<< orphan*/  printVersionFlag () ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
#define  required_argument 128 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 char* xStrdup (char*) ; 

__attribute__((used)) static CommandLineSettings parseArguments(int argc, char** argv) {

   CommandLineSettings flags = {
      .pidWhiteList = NULL,
      .userId = -1, // -1 is guaranteed to be an invalid uid_t (see setreuid(2))
      .sortKey = 0,
      .delay = -1,
      .useColors = true,
      .treeView = false,
   };

   static struct option long_opts[] =
   {
      {"help",     no_argument,         0, 'h'},
      {"version",  no_argument,         0, 'v'},
      {"delay",    required_argument,   0, 'd'},
      {"sort-key", required_argument,   0, 's'},
      {"user",     required_argument,   0, 'u'},
      {"no-color", no_argument,         0, 'C'},
      {"no-colour",no_argument,         0, 'C'},
      {"tree",     no_argument,         0, 't'},
      {"pid",      required_argument,   0, 'p'},
      {0,0,0,0}
   };

   int opt, opti=0;
   /* Parse arguments */
   while ((opt = getopt_long(argc, argv, "hvCs:td:u:p:", long_opts, &opti))) {
      if (opt == EOF) break;
      switch (opt) {
         case 'h':
            printHelpFlag();
            break;
         case 'v':
            printVersionFlag();
            break;
         case 's':
            if (strcmp(optarg, "help") == 0) {
               for (int j = 1; j < Platform_numberOfFields; j++) {
                  const char* name = Process_fields[j].name;
                  if (name) printf ("%s\n", name);
               }
               exit(0);
            }
            flags.sortKey = ColumnsPanel_fieldNameToIndex(optarg);
            if (flags.sortKey == -1) {
               fprintf(stderr, "Error: invalid column \"%s\".\n", optarg);
            }
            break;
         case 'd':
            if (sscanf(optarg, "%16d", &(flags.delay)) == 1) {
               if (flags.delay < 1) flags.delay = 1;
               if (flags.delay > 100) flags.delay = 100;
            } else {
               fprintf(stderr, "Error: invalid delay value \"%s\".\n", optarg);
            }
            break;
         case 'u':
            if (!Action_setUserOnly(optarg, &(flags.userId))) {
               fprintf(stderr, "Error: invalid user \"%s\".\n", optarg);
            }
            break;
         case 'C':
            flags.useColors = false;
            break;
         case 't':
            flags.treeView = true;
            break;
         case 'p': {
            char* argCopy = xStrdup(optarg);
            char* saveptr;
            char* pid = strtok_r(argCopy, ",", &saveptr);

            if(!flags.pidWhiteList) {
               flags.pidWhiteList = Hashtable_new(8, false);
            }

            while(pid) {
                unsigned int num_pid = atoi(pid);
                Hashtable_put(flags.pidWhiteList, num_pid, (void *) 1);
                pid = strtok_r(NULL, ",", &saveptr);
            }
            free(argCopy);

            break;
         }
         default:
            exit(1);
      }
   }
   return flags;
}