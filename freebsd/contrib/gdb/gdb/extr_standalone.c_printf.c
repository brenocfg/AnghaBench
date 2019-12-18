printf (int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
  char buffer[1024];
  sprintf (buffer, a1, a2, a3, a4, a5, a6, a7, a8, a9);
  display_string (buffer);
}