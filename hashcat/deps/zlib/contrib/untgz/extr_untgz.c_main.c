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
typedef  int /*<<< orphan*/  gzFile ;

/* Variables and functions */
#define  TGZ_EXTRACT 129 
#define  TGZ_LIST 128 
 char* TGZfname (char*) ; 
 int /*<<< orphan*/  TGZnotfound (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/ * gzopen (char*,char*) ; 
 int /*<<< orphan*/  help (int) ; 
 char* prog ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int tar (int /*<<< orphan*/ *,int,int,int,char**) ; 

int main(int argc,char **argv)
{
    int         action = TGZ_EXTRACT;
    int         arg = 1;
    char        *TGZfile;
    gzFile      *f;

    prog = strrchr(argv[0],'\\');
    if (prog == NULL)
      {
        prog = strrchr(argv[0],'/');
        if (prog == NULL)
          {
            prog = strrchr(argv[0],':');
            if (prog == NULL)
              prog = argv[0];
            else
              prog++;
          }
        else
          prog++;
      }
    else
      prog++;

    if (argc == 1)
      help(0);

    if (strcmp(argv[arg],"-l") == 0)
      {
        action = TGZ_LIST;
        if (argc == ++arg)
          help(0);
      }
    else if (strcmp(argv[arg],"-h") == 0)
      {
        help(0);
      }

    if ((TGZfile = TGZfname(argv[arg])) == NULL)
      TGZnotfound(argv[arg]);

    ++arg;
    if ((action == TGZ_LIST) && (arg != argc))
      help(1);

/*
 *  Process the TGZ file
 */
    switch(action)
      {
      case TGZ_LIST:
      case TGZ_EXTRACT:
        f = gzopen(TGZfile,"rb");
        if (f == NULL)
          {
            fprintf(stderr,"%s: Couldn't gzopen %s\n",prog,TGZfile);
            return 1;
          }
        exit(tar(f, action, arg, argc, argv));
      break;

      default:
        error("Unknown option");
        exit(1);
      }

    return 0;
}