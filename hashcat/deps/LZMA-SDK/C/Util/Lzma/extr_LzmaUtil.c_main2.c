#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UInt64 ;
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_6__ {int /*<<< orphan*/  file; int /*<<< orphan*/  vt; } ;
struct TYPE_5__ {int /*<<< orphan*/  file; int /*<<< orphan*/  vt; } ;
typedef  TYPE_1__ CFileSeqInStream ;
typedef  TYPE_2__ CFileOutStream ;
typedef  scalar_t__ BoolInt ;

/* Variables and functions */
 int Decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Encode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ False ; 
 int /*<<< orphan*/  FileOutStream_CreateVTable (TYPE_2__*) ; 
 int /*<<< orphan*/  FileSeqInStream_CreateVTable (TYPE_1__*) ; 
 int /*<<< orphan*/  File_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  File_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  File_GetLength (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ InFile_Open (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ OutFile_Open (int /*<<< orphan*/ *,char const*) ; 
 int PrintError (char*,char*) ; 
 int PrintErrorNumber (char*,int) ; 
 int /*<<< orphan*/  PrintHelp (char*) ; 
 int PrintUserError (char*) ; 
 int SZ_ERROR_DATA ; 
 int SZ_ERROR_MEM ; 
 int SZ_ERROR_READ ; 
 int SZ_ERROR_WRITE ; 
 int SZ_OK ; 
 scalar_t__ True ; 
 char* kCantAllocateMessage ; 
 char* kCantReadMessage ; 
 char* kCantWriteMessage ; 
 char* kDataErrorMessage ; 
 int strlen (char const*) ; 

__attribute__((used)) static int main2(int numArgs, const char *args[], char *rs)
{
  CFileSeqInStream inStream;
  CFileOutStream outStream;
  char c;
  int res;
  int encodeMode;
  BoolInt useOutFile = False;

  FileSeqInStream_CreateVTable(&inStream);
  File_Construct(&inStream.file);

  FileOutStream_CreateVTable(&outStream);
  File_Construct(&outStream.file);

  if (numArgs == 1)
  {
    PrintHelp(rs);
    return 0;
  }

  if (numArgs < 3 || numArgs > 4 || strlen(args[1]) != 1)
    return PrintUserError(rs);

  c = args[1][0];
  encodeMode = (c == 'e' || c == 'E');
  if (!encodeMode && c != 'd' && c != 'D')
    return PrintUserError(rs);

  {
    size_t t4 = sizeof(UInt32);
    size_t t8 = sizeof(UInt64);
    if (t4 != 4 || t8 != 8)
      return PrintError(rs, "Incorrect UInt32 or UInt64");
  }

  if (InFile_Open(&inStream.file, args[2]) != 0)
    return PrintError(rs, "Can not open input file");

  if (numArgs > 3)
  {
    useOutFile = True;
    if (OutFile_Open(&outStream.file, args[3]) != 0)
      return PrintError(rs, "Can not open output file");
  }
  else if (encodeMode)
    PrintUserError(rs);

  if (encodeMode)
  {
    UInt64 fileSize;
    File_GetLength(&inStream.file, &fileSize);
    res = Encode(&outStream.vt, &inStream.vt, fileSize, rs);
  }
  else
  {
    res = Decode(&outStream.vt, useOutFile ? &inStream.vt : NULL);
  }

  if (useOutFile)
    File_Close(&outStream.file);
  File_Close(&inStream.file);

  if (res != SZ_OK)
  {
    if (res == SZ_ERROR_MEM)
      return PrintError(rs, kCantAllocateMessage);
    else if (res == SZ_ERROR_DATA)
      return PrintError(rs, kDataErrorMessage);
    else if (res == SZ_ERROR_WRITE)
      return PrintError(rs, kCantWriteMessage);
    else if (res == SZ_ERROR_READ)
      return PrintError(rs, kCantReadMessage);
    return PrintErrorNumber(rs, res);
  }
  return 0;
}